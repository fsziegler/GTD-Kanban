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
recursive_mutex   UserData::m_mutex;

UserData::UserData()
{

   lock_guard<recursive_mutex> guard(m_mutex);
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
      for(auto itr: ms_gtdFixedCatMap)
      {
         TreeNode node(itr.second);
         m_gtdNodeTree.insert(TCatTreeNodeVectPair(itr.first, node));
      }
   }
}

UserData::~UserData()
{
}

const string &UserData::GetGTDCatStr(EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return (*ms_gtdFixedCatMap.find(category)).second;
}

const string* UserData::GetRepoSetStrPtr(const string& newItemStr) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return &(*ms_itemRepoSet.insert(newItemStr).first);
}

bool UserData::IsStrInSystem(const string& newItemStr) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return (ms_itemRepoSet.end() != ms_itemRepoSet.find(newItemStr));
}

int UserData::GetCategoryStrCount(EnumGTDCategory category,
      const string& itemStr) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   int nCnt(0);
   size_t tmpIndex(0);
   while(getCategoryCTreeNodeVect(category).size() > tmpIndex)
   {
      if (itemStr
            == GetNodeNameStr(getCategoryCTreeNodeVect(category), tmpIndex))
      {
         ++nCnt;
      }
      ++tmpIndex;
   }
   return nCnt;
}

bool UserData::FindNthCategoryStrIndex(EnumGTDCategory category,
      const string& itemStr, const size_t n, size_t& index) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   size_t nCnt(0);
   size_t tmpIndex(0);
   while(getCategoryCTreeNodeVect(category).size() > tmpIndex)
   {
      if (itemStr
            == GetNodeNameStr(getCategoryCTreeNodeVect(category), tmpIndex))
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

bool UserData::GetNthCategoryStr(EnumGTDCategory category,
      const size_t& index, string& itemStr) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if(getCategoryCTreeNodeVect(category).size() <= index)
   {
      return false;
   }
   itemStr = GetNodeNameStr(
         getCategoryCTreeNodeVect(category), index);
   return true;
}

void UserData::DumpGTDCategory(EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   cout << *GetCTreeNode(category).getMpNodeNameStrPtr() << ":"
         << endl;
   if(getCategoryCTreeNodeVect(category).empty())
   {
      cout << "  (empty)" << endl;
   }
   else
   {
      int cnt(1);
      for(auto itr: getCategoryCTreeNodeVect(category))
      {
         DumpTreeNode(itr, cnt, 1);
      }
   }
}

void UserData::DumpAllGTD() const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   for(auto itr: ms_gtdFixedCatMap)
   {
      DumpGTDCategory(itr.first);
   }
}

const TTreeNodeVect& UserData::getCategoryCTreeNodeVect(
      EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return (*m_gtdNodeTree.find(category)).second.getChildren();
}

const TCatTreeNodeVectMap& UserData::getGtdNodeTree() const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return m_gtdNodeTree;
}

const TreeNode& UserData::GetCTreeNode(EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   auto itr(m_gtdNodeTree.find(category));
   if(m_gtdNodeTree.end() == itr)
   {
      throw;
   }
   return (*itr).second;
}

const TGTDCategoryMap& UserData::getGtdFixedCatMap()
{
   return ms_gtdFixedCatMap;
}

size_t UserData::AddStrToCategory(const string& newItemStr,
      EnumGTDCategory category)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   TreeNode& treeNode = GetTreeNode(category);
   if(0 < newItemStr.size())
   {
      TreeNode node(newItemStr);
      treeNode.AddChildNode(node);
   }
   return treeNode.getChildren().size();
}

size_t UserData::AddDelimStrToCategory(const string& newItemsStr,
      EnumGTDCategory category, char delim)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   size_t pos = newItemsStr.find_first_of(delim);
   // Case of no delimiter in string
   if (string::npos == pos)
   {
      AddStrToCategory(newItemsStr);
      return GetTreeNode(category).getChildren().size();
   }
   string workingStr(newItemsStr);
   while (string::npos != pos)
   {
      const string currStr = workingStr.substr(0, pos);
      AddStrToCategory(currStr);
      {
         string newSrcStr(workingStr.substr(pos + 1));
         workingStr = newSrcStr;
      }
      pos = workingStr.find_first_of(delim);
   }
   if (0 < workingStr.size())
   {
      AddStrToCategory(workingStr);
   }
   return GetTreeNode(category).getChildren().size();
}

bool UserData::MoveNthStrBetweenCategories(const string& itemStr,
      EnumGTDCategory fromCat, EnumGTDCategory toCat, size_t n)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if(!IsStrInSystem(itemStr))
   {
      return false;
   }
   size_t index;  // index is the position of itemStr in the fromCat vector
   if(!FindNthCategoryStrIndex(fromCat, itemStr, n, index))
   {
      return false;
   }

   // Add item to the toCat category
   TreeNode node(itemStr);
   TreeNode& catNode = GetTreeNode(toCat);
   catNode.AddChildNode(node);

   // Remove item from fromCat category
   GetTreeNode(fromCat).RemoveNthChild(index);
   return true;
}

bool UserData::MoveNthStrBetweenCategories(const string& itemStr,
      date newDate, EnumGTDCategory fromCat, EnumGTDCategory toCat,
      size_t n)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if(!MoveNthStrBetweenCategories(itemStr, fromCat, toCat, n))
   {
      return false;
   }
   TreeNode& catNode = GetTreeNode(toCat);
   catNode.SetDate(newDate, kLastChildNode);
   return true;
}

bool UserData::MoveNthStrBetweenCategories(const string& itemStr,
      date newDate, ptime newTime, EnumGTDCategory fromCat,
      EnumGTDCategory toCat, size_t n)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if(!MoveNthStrBetweenCategories(itemStr, fromCat, toCat, n))
   {
      return false;
   }
   TreeNode& catNode = GetTreeNode(toCat);
   catNode.SetDateTime(newDate, newTime, kLastChildNode);
   return true;
}

TreeNode& UserData::GetTreeNode(EnumGTDCategory category)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   auto itr(m_gtdNodeTree.find(category));
   if(m_gtdNodeTree.end() == itr)
   {
      throw;
   }
   return (*itr).second;
}

const TTreeNodeVect& UserData::getCategoryCTreeNodeVect(
      EnumGTDCategory category)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return (*m_gtdNodeTree.find(category)).second.getChildren();
}

const string& UserData::GetNodeNameStr(const TTreeNodeVect& treeNodeVect,
      size_t index) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return *treeNodeVect[index].getMpNodeNameStrPtr();
}

void UserData::PopulateCStrPtrSetFromTreeNode(const TreeNode& treeNode,
      TCStrPtrSet& strPtrSet) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   strPtrSet.insert(treeNode.getMpNodeNameStrPtr());
   for(auto itr: treeNode.getChildren())
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

void UserData::DumpTreeNode(const TreeNode& treeNode, int& cnt,
      int indent) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   DumpIndent(indent);
   cout << cnt++ << ") "<< *treeNode.getMpNodeNameStrPtr() << endl;
   for(auto itr: treeNode.getChildren())
   {
      DumpTreeNode(itr, cnt, indent+1);
   }
}

size_t UserData::CleanUpRepoSet()
{
   // Add in-basket contents to newRepoSet
   TCStrPtrSet newRepoSet;
   for(auto itr: getCategoryCTreeNodeVect())
   {
      newRepoSet.insert(itr.getMpNodeNameStrPtr());
   }
   // Add GTD tree contents to newRepoSet
   for(auto itr: m_gtdNodeTree)
   {
      PopulateCStrPtrSetFromTreeNode(itr.second, newRepoSet);
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
