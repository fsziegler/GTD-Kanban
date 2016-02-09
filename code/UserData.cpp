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
#include "BoostJSON.h"
#include <iostream>
#include <fstream>
#include <boost/thread/lock_guard.hpp>

using namespace BoostJSONDemo;

namespace ZiegGTDKanban
{

TGTDCategoryMap   UserData::ms_gtdFixedCatMap;
recursive_mutex   UserData::m_mutex;

UserData& UserData::getInst()
{
   static UserData instance;
   return instance;
}

UserData::UserData()
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if (0 == ms_gtdFixedCatMap.size())
   {
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kInBasket, "In Basket"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kSomedayMaybe, "Someday Maybe"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kReference, "Reference"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kDoIt, "Do It!"));
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
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kTrash, "(Trash)"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kKanbanReady, "Kanban Ready"));
            ms_gtdFixedCatMap.insert(
                  TGTDCategoryPair(EnumGTDCategory::kKanbanDoing,
                                   "Kanban Doing"));
            ms_gtdFixedCatMap.insert(
                  TGTDCategoryPair(EnumGTDCategory::kKanbanDone,
                                   "Kanban Done"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kMoveQueue, "(Move Queue)"));
      ms_gtdFixedCatMap.insert(
            TGTDCategoryPair(EnumGTDCategory::kGTDCategoryUNKNOWN,
                  "(GTD Category UNKNOWN)"));

      PopulateGTDNodeTree();
   }
}

UserData::~UserData()
{
}

bool UserData::ReadStrAtRow(EnumGTDCategory category, size_t row,
      string& rowStr) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   const TreeNode& treeNode = GetCTreeNode(category);
   // Incrementing row here because the top level category node does not count
   return treeNode.ReadStrAtRow(row + 1, rowStr);
}

//const string &UserData::GetGTDCatStr(EnumGTDCategory category) const
//{
//   lock_guard<recursive_mutex> guard(m_mutex);
//   return (*ms_gtdFixedCatMap.find(category)).second;
//}
//
//int UserData::GetCategoryStrCount(EnumGTDCategory category,
//      const string& itemStr) const
//{
//   lock_guard<recursive_mutex> guard(m_mutex);
//   int nCnt(0);
//   size_t tmpIndex(0);
//   while(getCategoryCTreeNodeVect(category).size() > tmpIndex)
//   {
//      if (itemStr
//            == GetNodeNameStr(getCategoryCTreeNodeVect(category), tmpIndex))
//      {
//         ++nCnt;
//      }
//      ++tmpIndex;
//   }
//   return nCnt;
//}
//
//bool UserData::FindNthCategoryStrIndex(EnumGTDCategory category,
//      const string& itemStr, const size_t n, size_t& index) const
//{
//   lock_guard<recursive_mutex> guard(m_mutex);
//   size_t nCnt(0);
//   size_t tmpIndex(0);
//   while(getCategoryCTreeNodeVect(category).size() > tmpIndex)
//   {
//      if (itemStr
//            == GetNodeNameStr(getCategoryCTreeNodeVect(category), tmpIndex))
//      {
//         if(n == nCnt)
//         {
//            index = tmpIndex;
//            return true;
//         }
//         ++nCnt;
//      }
//      ++tmpIndex;
//   }
//   return false;
//}

bool UserData::GetNthCategoryStr(EnumGTDCategory category, const size_t& index,
      string& itemStr) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if (getCategoryCTreeNodeVect(category).size() <= index)
   {
      return false;
   }
   itemStr = GetNodeNameStr(getCategoryCTreeNodeVect(category), index);
   return true;
}

void UserData::DumpGTDCategory(EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   cout << GetCTreeNode(category).getMpNodeNameStr() << ":" << endl;
   if (getCategoryCTreeNodeVect(category).empty())
   {
      cout << "  (empty)" << endl;
   }
   else
   {
      int cnt(1);
      for (auto itr : getCategoryCTreeNodeVect(category))
      {
         DumpTreeNode(itr, cnt, 1);
      }
   }
}

void UserData::DumpAllGTD() const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   for (auto itr : ms_gtdFixedCatMap)
   {
      DumpGTDCategory(itr.first);
   }
}

void UserData::DumpAllToJSONFile(const string& jsonFileNameStr) const
{
   ofstream jsonOutFile;
   jsonOutFile.open(jsonFileNameStr);
   jsonOutFile << "{\n  \"GTD Node Tree\":{";
   size_t indent(1);
   bool first(true);
   for (auto itr : m_gtdNodeTree)
   {
      jsonOutFile << (first ? "" : ",");
      jsonOutFile << endl;
      first = false;
      itr.second.DumpAllToJSONFile(indent, jsonOutFile);
   }
   jsonOutFile << endl << "  }" << endl << "}";
   jsonOutFile.close();
}

void CheckCategoryNameStrThrow(const string& catStr, const UserData& userData)
{
   if ((0 == catStr.size())
         || (EnumGTDCategory::kGTDCategoryUNKNOWN
               == userData.LookUpCategory(catStr)))
   {
      throw;
   }
   EnumGTDCategory nodeCat(userData.LookUpCategory(catStr));
   if (userData.getGtdNodeTree().end()
         != userData.getGtdNodeTree().find(nodeCat))
   {
      throw;   // Each category should only show up once
   }
}

const string kGTDNodeTreeStr("GTD Node Tree");
bool UserData::LoadFromJSONFile(const string& jsonFileNameStr,
      bool clearExisting)
{
   if (!exists(jsonFileNameStr))
   {
      return false;
   }

   BoostJSON bjson;
   bjson.LoadJSONFile(jsonFileNameStr);
   ptree::const_iterator gtdItr = bjson.getPt().begin();
   bool validJSON(false);
   while (bjson.getPt().end() != gtdItr)
   {
      if ((0 < (*gtdItr).first.size())
            && (0 == kGTDNodeTreeStr.compare((*gtdItr).first)))
      {
         validJSON = true;
         break;
      }
      ++gtdItr;
   }
   if (!validJSON)
   {
      return false;
   }
   if (clearExisting)
   {
      m_gtdNodeTree.clear();  // Now you know you have a valid JSON file
   }

   for (auto itr : (*gtdItr).second)
   {
      const string& nodeNameStr = itr.first;
      // All of the JSON comprises named objects with a valid category name
//      CheckCategoryNameStrThrow(nodeNameStr, *this);
      EnumGTDCategory nodeCat(LookUpCategory(nodeNameStr));
      TreeNode node(nodeNameStr);
      TreeNode& catNode = (*m_gtdNodeTree.insert(
            TCatTreeNodeVectPair(nodeCat, node)).first).second;
      catNode.LoadPTree(itr.second);
   }
   DumpAllGTD();

   return true;
}

void UserData::Clear()
{
   lock_guard<recursive_mutex> guard(m_mutex);
   m_gtdNodeTree.clear();
   PopulateGTDNodeTree();
}

void UserData::PopulateGTDNodeTree()
{
   for (auto itr : ms_gtdFixedCatMap)
   {
      TreeNode node(itr.second);
      m_gtdNodeTree.insert(TCatTreeNodeVectPair(itr.first, node));
   }
}

TreeNode& UserData::GetTreeNode(EnumGTDCategory category)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   auto itr(m_gtdNodeTree.find(category));
   if (m_gtdNodeTree.end() == itr)
   {
      throw;
   }
   return (*itr).second;
}

const TreeNode& UserData::GetCTreeNode(EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   auto itr(m_gtdNodeTree.find(category));
   if (m_gtdNodeTree.end() == itr)
   {
      throw;
   }
   return (*itr).second;
}

const TGTDCategoryMap& UserData::getGtdFixedCatMap()
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return ms_gtdFixedCatMap;
}

EnumGTDCategory UserData::LookUpCategory(const string& categoryStr)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   for (auto itr : ms_gtdFixedCatMap)
   {
      if (categoryStr == itr.second)
      {
         return itr.first;
      }
   }
   return EnumGTDCategory::kGTDCategoryUNKNOWN;
}

size_t UserData::AddStrToCategory(const string& newItemStr,
      EnumGTDCategory category)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   TreeNode& treeNode = GetTreeNode(category);
   if (0 < newItemStr.size())
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

void UserData::ReplaceCategoryTree(EnumGTDCategory category,
      const TTreeNodeVect& children)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   TreeNode& node = GetTreeNode(category);
   node.ClearAllChildren();
   node.AppendChildren(children);
}

bool UserData::MoveNthStrBetweenCategories(const string& itemStr,
      EnumGTDCategory srcCat, EnumGTDCategory tgtCat, size_t row)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   if (!TreeNode::IsStrInSystem(itemStr))
   {
      return false;
   }
   // row is incremented here because the initial node is the root node
   if (!GetTreeNode(srcCat).RemoveNodeAtRow(itemStr, row + 1))
   {
      return false;
   }
   TreeNode newNode(itemStr);
   GetTreeNode(tgtCat).AddChildNode(newNode);
   return true;
}

size_t UserData::MoveAllBetweenCategories(EnumGTDCategory srcCat,
      EnumGTDCategory tgtCat)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   TreeNode& tgtNode = GetTreeNode(tgtCat);
   if (TreeNode::getNonExistentTreeNode() == tgtNode)
   {
      throw;
   }
   tgtNode.AppendChildren(GetTreeNode(srcCat).getChildren());
   TreeNode& srcTreeNode = GetTreeNode(srcCat);
   const size_t numMoved(GetTreeNode(srcCat).getChildren().size());
   srcTreeNode.ClearAllChildren();
   return numMoved;
}

const TTreeNodeVect& UserData::getCategoryCTreeNodeVect(
      EnumGTDCategory category) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return GetCTreeNode(category).getChildren();
}

const string& UserData::GetNodeNameStr(const TTreeNodeVect& treeNodeVect,
      size_t index) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return treeNodeVect[index].getMpNodeNameStr();
}

void UserData::PopulateCStrPtrSetFromTreeNode(const TreeNode& treeNode,
      TCStrPtrSet& strPtrSet) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   strPtrSet.insert(treeNode.getMpNodeNameStrPtr());
   for (auto itr : treeNode.getChildren())
   {
      PopulateCStrPtrSetFromTreeNode(itr, strPtrSet);
   }
}

void UserData::DumpIndent(int indent) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   for (int i = 0; indent > i; ++i)
   {
      cout << "  ";
   }
}

void UserData::DumpTreeNode(const TreeNode& treeNode, int& cnt,
      int indent) const
{
   lock_guard<recursive_mutex> guard(m_mutex);
   DumpIndent(indent);
   cout << cnt++ << ") " << treeNode.getMpNodeNameStr() << endl;
   for (auto itr : treeNode.getChildren())
   {
      DumpTreeNode(itr, cnt, indent + 1);
   }
}

const TCatTreeNodeVectMap& UserData::getGtdNodeTree() const
{
   return m_gtdNodeTree;
}

} /* namespace ZiegGTDKanban */
