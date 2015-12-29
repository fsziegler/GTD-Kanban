/*
 File: UserData.cpp

 Created on: Dec 27, 2015@5:00:58 PM
 Author: fred
 The MIT License (MIT)

 Copyright (c) 2015 Frederick S. Ziegler

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 */
#include "UserData.h"

namespace ZiegGTDKanban
{

TStrSet UserData::ms_itemRepoSet;
UserData::UserData()
{
   m_gtdFixedCatMap.insert(TGTDCategoryPair(kInBasket, "In Basket"));
   m_gtdFixedCatMap.insert(TGTDCategoryPair(kSomedayMaybe, "Someday Maybe"));
   m_gtdFixedCatMap.insert(TGTDCategoryPair(kReference, "Reference"));
   m_gtdFixedCatMap.insert(
         TGTDCategoryPair(kWaitingForAnotherPerson,
               "Waiting for Another Person"));
   m_gtdFixedCatMap.insert(TGTDCategoryPair(kCalendar, "Calendar"));
   m_gtdFixedCatMap.insert(
         TGTDCategoryPair(kProjectsToPlan, "Projects-to-Plan"));
   m_gtdFixedCatMap.insert(TGTDCategoryPair(kProjectPlans, "Project Plans"));
   m_gtdFixedCatMap.insert(TGTDCategoryPair(kNextActions, "Next Actions"));
}

UserData::~UserData()
{
}

const string &UserData::GetGTDCatStr(EnumGTDCategory category) const
{
   return (*m_gtdFixedCatMap.find(category)).second;
}

const string* UserData::GetRepoSetStrPtr(const string& newItemStr)
{
   return &(*ms_itemRepoSet.insert(newItemStr).first);
}

bool UserData::IsItemInSystem(const string& newItemStr) const
{
   return (ms_itemRepoSet.end() != ms_itemRepoSet.find(newItemStr));
}

int UserData::GetItemCountInBasket(const string& itemStr) const
{
   int nCnt(0);
   size_t tmpIndex(0);
   while(m_inBasketVect.size() > tmpIndex)
   {
      if(itemStr == *m_inBasketVect[tmpIndex])
      {
         ++nCnt;
      }
      ++tmpIndex;
   }
   return nCnt;
}

bool UserData::FindNthInBasketItem(const string& itemStr, const size_t n,
      size_t& index) const
{
   size_t nCnt(0);
   size_t tmpIndex(0);
   while(m_inBasketVect.size() > tmpIndex)
   {
      if(itemStr == *m_inBasketVect[tmpIndex])
      {
         if(n == nCnt)
         {
            index = tmpIndex;
            return true;
         }
         ++nCnt;
      }
      ++tmpIndex;
   }
   return false;
}

void UserData::AddItemToInBasket(const string& newItemStr)
{
   auto setStrItr(ms_itemRepoSet.insert(newItemStr).first);
   m_inBasketVect.push_back(&(*setStrItr));
}

bool UserData::MoveNthInBasketItemToGTD(const string& itemStr,
      EnumGTDCategory category, size_t n)
{
   if(!IsItemInSystem(itemStr))
   {
      return false;
   }
   size_t index;
   if(!FindNthInBasketItem(itemStr, n, index))
   {
      return false;
   }

   // Add item to GTD category
   TreeNode node;
   InitNode(itemStr, node);
   TTreeNodeVect& catNodeVect = GetTreeNodeVect(category);
   catNodeVect.push_back(node);

   // Remove item from in-basket
   // TODO Rework this to move all items after n forward on and delete last item
   TStrPtrVect tmpVect;
   for (size_t i = 0; m_inBasketVect.size() > i; ++i)
   {
      if(n != i)
      {
         tmpVect.push_back(m_inBasketVect[i]);
      }
   }
   m_inBasketVect = tmpVect;
   return true;
}

bool UserData::MoveNthInBasketItemToGTD(const string& itemStr,
      EnumGTDCategory category, const date& newDate, size_t n)
{
   if(!MoveNthInBasketItemToGTD(itemStr, category, n))
   {
      return false;
   }
   TTreeNodeVect& catNodeVect = GetTreeNodeVect(category);
   catNodeVect.back().m_date = newDate;
   return true;
}

bool UserData::MoveNthInBasketItemToGTD(const string& itemStr,
      EnumGTDCategory category, const date& newDate, const ptime& newTime,
      size_t n)
{
   if(!MoveNthInBasketItemToGTD(itemStr, category, n))
   {
      return false;
   }
   TTreeNodeVect& catNodeVect = GetTreeNodeVect(category);
   catNodeVect.back().m_date = newDate;
   catNodeVect.back().m_time = newTime;
   return true;
}


void UserData::InitNode(const string& itemStr, TreeNode& node) const
{
   node.mp_nodeNameStrPtr = GetRepoSetStrPtr(itemStr);
   if(!node.m_date.is_not_a_date())
   {
      node.m_date = date(special_values::not_a_date_time);
   }
   node.m_time = special_values::not_a_date_time;
}

TTreeNodeVect& UserData::GetTreeNodeVect(EnumGTDCategory category)
{
   auto itr(m_gtdNodeTree.find(category));
   if(m_gtdNodeTree.end() == itr)
   {
      throw;
   }
   return (*itr).second;
}

void UserData::PopulateCStrPtrSetFromTreeNode(const TreeNode& treeNode,
      TCStrPtrSet& strPtrSet) const
{
   strPtrSet.insert(treeNode.mp_nodeNameStrPtr);
   for (auto itr = treeNode.m_children.begin();
         treeNode.m_children.end() != itr; ++itr)
   {
      PopulateCStrPtrSetFromTreeNode(*itr, strPtrSet);
   }
}

size_t UserData::CleanUpRepoSet()
{
   // Add in-basket contents to newRepoSet
   TCStrPtrSet newRepoSet;
   for(auto itr = m_inBasketVect.begin(); m_inBasketVect.end() != itr; ++itr)
   {
      newRepoSet.insert(*itr);
   }
   // Add GTD tree contents to newRepoSet
   for(auto itr = m_gtdNodeTree.begin(); m_gtdNodeTree.end() != itr; ++itr)
   {
      const TTreeNodeVect& nodeVect = (*itr).second;
      for (auto treeNodeItr = nodeVect.begin(); nodeVect.end() != treeNodeItr;
            ++treeNodeItr)
      {
         const TreeNode& treeNode = *treeNodeItr;
         PopulateCStrPtrSetFromTreeNode(treeNode, newRepoSet);
      }
   }
   // Remove all strings not in newSet from ms_itemRepoSet
   const size_t diff(ms_itemRepoSet.size() - newRepoSet.size());
   if(0 != diff)
   {
      TCStrPtrSet removeSet;
      for(auto itr = ms_itemRepoSet.begin(); ms_itemRepoSet.end() != itr; ++itr)
      {
         if(newRepoSet.end() == newRepoSet.find(&(*itr)))
         {
            removeSet.insert(&(*itr));
         }
      }
      for(auto itr = removeSet.begin(); removeSet.end() != itr; ++itr)
      {
         string removeStr(*(*itr));
         ms_itemRepoSet.erase(ms_itemRepoSet.find(removeStr));
      }
   }
   return diff;
}

} /* namespace ZiegGTDKanban */
