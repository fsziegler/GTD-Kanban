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
#include <boost/thread/lock_guard.hpp>

namespace ZiegGTDKanban
{

TGTDCategoryMap   UserData::ms_gtdFixedCatMap;
TStrSet           UserData::ms_itemRepoSet;
mutex             UserData::m_mutex;

UserData::UserData()
{
   lock_guard<mutex> guard(m_mutex);
   if(0 == ms_gtdFixedCatMap.size())
   {
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kInBasket, "In Basket"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kSomedayMaybe, "Someday Maybe"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kReference, "Reference"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kWaitingForAnotherPerson,
                  "Waiting for Another Person"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kCalendar, "Calendar"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kProjectsToPlan,
                  "Projects-to-Plan"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kProjectPlans, "Project Plans"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kNextActions, "Next Actions"));
   }
}

UserData::~UserData()
{
}

const string &UserData::GetGTDCatStr(EnumGTDCategory category) const
{
   lock_guard<mutex> guard(m_mutex);
   return (*ms_gtdFixedCatMap.find(category)).second;
}

const string* UserData::GetRepoSetStrPtr(const string& newItemStr) const
{
   lock_guard<mutex> guard(m_mutex);
   return &(*ms_itemRepoSet.insert(newItemStr).first);
}

bool UserData::IsItemInSystem(const string& newItemStr) const
{
   lock_guard<mutex> guard(m_mutex);
   return (ms_itemRepoSet.end() != ms_itemRepoSet.find(newItemStr));
}

int UserData::GetItemCountInBasket(const string& itemStr) const
{
   lock_guard<mutex> guard(m_mutex);
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
   lock_guard<mutex> guard(m_mutex);
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

void UserData::DumpInBasket() const
{
   lock_guard<mutex> guard(m_mutex);
   cout << "In-basket:" << endl;
   for(auto itr: m_inBasketVect)
   {
      cout << "  " << *itr << endl;
   }
}

void UserData::DumpGTDCategory(EnumGTDCategory category) const
{
   lock_guard<mutex> guard(m_mutex);
   cout << (*ms_gtdFixedCatMap.find(category)).second << endl;
   for(auto itr: (*m_gtdNodeTree.find(category)).second)
   {
      DumpTreeNode(itr, 1);
   }
}

void UserData::DumpAllGTD() const
{
   lock_guard<mutex> guard(m_mutex);
   for(auto itr: ms_gtdFixedCatMap)
   {
      DumpGTDCategory(itr.first);
   }
}

const TStrPtrVect& UserData::getInBasketVect() const
{
   lock_guard<mutex> guard(m_mutex);
   return m_inBasketVect;
}

const TCatTreeNodeVectMap& UserData::getGtdNodeTree() const
{
   lock_guard<mutex> guard(m_mutex);
   return m_gtdNodeTree;
}

const TTreeNodeVect& UserData::GetCTreeNodeVect(EnumGTDCategory category) const
{
   lock_guard<mutex> guard(m_mutex);
   auto itr(m_gtdNodeTree.find(category));
   if(m_gtdNodeTree.end() == itr)
   {
      throw;
   }
   return (*itr).second;
}

void UserData::AddItemToInBasket(const string& newItemStr)
{
   lock_guard<mutex> guard(m_mutex);
   if(0 < newItemStr.size())
   {
      auto setStrItr(ms_itemRepoSet.insert(newItemStr).first);
      m_inBasketVect.push_back(&(*setStrItr));
   }
}

void UserData::AddItemsToInBasket(const string& newItemsStr, char delim)
{
   lock_guard<mutex> guard(m_mutex);
   size_t pos = newItemsStr.find_first_of(delim);
   // Case of no delimiter in string
   if (string::npos == pos)
   {
      AddItemToInBasket(newItemsStr);
      return;
   }
   string workingStr(newItemsStr);
   while (string::npos != pos)
   {
      const string currStr = workingStr.substr(0, pos);
      AddItemToInBasket(currStr);
      {
         string newSrcStr(workingStr.substr(pos + 1));
         workingStr = newSrcStr;
      }
      pos = workingStr.find_first_of(delim);
   }
   if (0 < workingStr.size())
   {
      AddItemToInBasket(workingStr);
   }
}

bool UserData::MoveNthInBasketItemToGTD(const string& itemStr,
      EnumGTDCategory category, size_t n)
{
   lock_guard<mutex> guard(m_mutex);
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
      const date& newDate, EnumGTDCategory category, size_t n)
{
   lock_guard<mutex> guard(m_mutex);
   if(!MoveNthInBasketItemToGTD(itemStr, category, n))
   {
      return false;
   }
   TTreeNodeVect& catNodeVect = GetTreeNodeVect(category);
   catNodeVect.back().m_date = newDate;
   return true;
}

bool UserData::MoveNthInBasketItemToGTD(const string& itemStr,
      const date& newDate, const ptime& newTime, EnumGTDCategory category,
      size_t n)
{
   lock_guard<mutex> guard(m_mutex);
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
   lock_guard<mutex> guard(m_mutex);
   node.mp_nodeNameStrPtr = GetRepoSetStrPtr(itemStr);
   if(!node.m_date.is_not_a_date())
   {
      node.m_date = date(special_values::not_a_date_time);
   }
   node.m_time = special_values::not_a_date_time;
}

TTreeNodeVect& UserData::GetTreeNodeVect(EnumGTDCategory category)
{
   lock_guard<mutex> guard(m_mutex);
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
   lock_guard<mutex> guard(m_mutex);
   strPtrSet.insert(treeNode.mp_nodeNameStrPtr);
   for(auto itr: treeNode.m_children)
   {
      PopulateCStrPtrSetFromTreeNode(itr, strPtrSet);
   }
}

void UserData::DumpIndent(int indent) const
{
   for(int i = 0; indent > i; ++i)
   {
      cout << "  ";
   }
}

void UserData::DumpTreeNode(const TreeNode& treeNode, int indent) const
{
   lock_guard<mutex> guard(m_mutex);
   DumpIndent(indent);
   cout << treeNode.mp_nodeNameStrPtr << endl;
   for(auto itr: treeNode.m_children)
   {
      DumpTreeNode(itr, indent+1);
   }
}

size_t UserData::CleanUpRepoSet()
{
   // Add in-basket contents to newRepoSet
   TCStrPtrSet newRepoSet;
   for(auto itr: m_inBasketVect)
   {
      newRepoSet.insert(itr);
   }
   // Add GTD tree contents to newRepoSet
   for(auto itr: m_gtdNodeTree)
   {
      const TTreeNodeVect& nodeVect = itr.second;
      for (auto treeNodeItr: nodeVect)
      {
         PopulateCStrPtrSetFromTreeNode(treeNodeItr, newRepoSet);
      }
   }
   // Remove all strings not in newSet from ms_itemRepoSet
   const size_t diff(ms_itemRepoSet.size() - newRepoSet.size());
   if(0 != diff)
   {
      TCStrPtrSet removeSet;
      for(auto itr: ms_itemRepoSet)
      {
         if(newRepoSet.end() == newRepoSet.find(&itr))
         {
            removeSet.insert(&itr);
         }
      }
      for(auto itr: removeSet)
      {
         string removeStr(*itr);
         ms_itemRepoSet.erase(ms_itemRepoSet.find(removeStr));
      }
   }
   return diff;
}

} /* namespace ZiegGTDKanban */