/*
 File: TreeNode.cpp

 Created on: Dec 30, 2015@4:28:13 PM
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
#include "TreeNode.h"
#include <fstream>
#include <boost/thread/lock_guard.hpp>

namespace ZiegGTDKanban
{

TStrSet           TreeNode::ms_itemRepoSet;
recursive_mutex   TreeNode::m_mutex;
unsigned long     TreeNode::m_maxUniqueID(0);

TreeNode NonExistentTreeNode("NonExistentTreeNode");

TreeNode::TreeNode(const string& newItemStr, TreeNode* parentNode)
: mp_parentNode(parentNode),
  mp_nodeNameStrPtr(GetRepoSetStrPtr(newItemStr)),
  m_date(special_values::not_a_date_time),
  m_time(special_values::not_a_date_time),
  m_expanded(true),
  m_uniqueID(++m_maxUniqueID)
{
}

TreeNode::~TreeNode()
{
}

TreeNode::TreeNode(const TreeNode& rhs)
{
   SetEqualTo(rhs);
}

TreeNode& TreeNode::operator=(const TreeNode& rhs)
{
   SetEqualTo(rhs);
   return *this;
}

bool TreeNode::operator==(const TreeNode& rhs)
{
   return IsEqualTo(rhs);
}

bool TreeNode::operator!=(const TreeNode& rhs)
{
   return !IsEqualTo(rhs);
}

TreeNode& TreeNode::operator[](size_t index)
{
   if(0 == index)
   {
      return *this;
   }
   if(CalcNestedChildCount() < index)
   {
      return NonExistentTreeNode;
   }
   size_t tmpIndex(index - 1);
   for(size_t i = 0; m_children.size() > i; ++i)
   {
      if(0 == tmpIndex)
      {
         TreeNode& retNode = m_children[i];
         return retNode;
      }
      --tmpIndex;
      if(m_children[i].CalcNestedChildCount() > tmpIndex)
      {
         TreeNode& retNode = m_children[i][tmpIndex];
         return retNode;
      }
      tmpIndex -= m_children[i].CalcNestedChildCount();
   }
   // We should never reach this point
   return NonExistentTreeNode;
}

TreeNode& TreeNode::getNonExistentTreeNode()
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return NonExistentTreeNode;
}

const string* TreeNode::GetRepoSetStrPtr(const string& newItemStr)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   ms_itemRepoSet.insert(newItemStr);
   return &(*ms_itemRepoSet.insert(newItemStr).first);
}

bool TreeNode::IsStrInSystem(const string& newItemStr)
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return (ms_itemRepoSet.end() != ms_itemRepoSet.find(newItemStr));
}

unsigned int TreeNode::GetNumInstancesOfItemStr(const string& itemStr,
      TNodeLocationDeque &lastIndexDeque) const
{
   unsigned int cnt(0);
   if (0 == itemStr.compare(*mp_nodeNameStrPtr))
   {
      ++cnt;
      lastIndexDeque.push_back(0);
   }

   for(size_t i = 0; m_children.size() > i; ++i)
   {
      lastIndexDeque.push_back(i);
      if(m_children[i].GetNumInstancesOfItemStr(itemStr, lastIndexDeque))
      {
         ++cnt;
      }
      else
      {
         lastIndexDeque.pop_back();
      }
   }
   return cnt;
}

size_t TreeNode::CalcNestedChildCount() const
{
   size_t childCnt(m_children.size());
   for(auto itr: m_children)
   {
      childCnt += itr.CalcNestedChildCount();
   }
   return childCnt;
}

void TreeNode::IndentJSONFile(size_t indent, ofstream& jsonOutFile) const
{
   size_t i(indent);
   while(i)
   {
      jsonOutFile << "  ";
      --i;
   }
}

void TreeNode::DumpAllToJSONFile(size_t indent, ofstream& jsonOutFile) const
{
//   const string*           mp_nodeNameStrPtr;
//   date                    m_date;
//   ptime                   m_time;
//   TTreeNodeVect           m_children;
   IndentJSONFile(indent + 1, jsonOutFile);
   string nodeNameStr;
   FormatWithBackslash(*mp_nodeNameStrPtr, nodeNameStr);
   jsonOutFile << "\"" << nodeNameStr << "\": {" << endl;
   {
      IndentJSONFile(indent + 2, jsonOutFile);
      jsonOutFile << "\"date\" : \"" << m_date << "\"," << endl;
      IndentJSONFile(indent + 2, jsonOutFile);
      jsonOutFile << "\"time\" : \"" << m_time << "\"," << endl;
      IndentJSONFile(indent + 2, jsonOutFile);
      jsonOutFile << "\"expand\" : \"" << (m_expanded ? "true" : "false")
            << "\"," << endl;
      IndentJSONFile(indent + 2, jsonOutFile);
      jsonOutFile << "\"uniqueID\" : \"" << m_uniqueID << "\"," << endl;
      IndentJSONFile(indent + 2, jsonOutFile);
      jsonOutFile << "\"children\" : {";
      bool first(true);
      for(auto itr: m_children)
      {
         jsonOutFile << (first ? "" : ",");
         jsonOutFile << endl;
         first = false;
         itr.DumpAllToJSONFile(indent + 2, jsonOutFile);
      }
      jsonOutFile << endl;
      IndentJSONFile(indent + 2, jsonOutFile);
      jsonOutFile << "}" << endl;
   }
   IndentJSONFile(indent + 1, jsonOutFile);
   jsonOutFile << "}";
}

TreeNode& TreeNode::AddChildNode(TreeNode& childNode)
{
   m_children.push_back(childNode);
   return m_children.back();
}

void TreeNode::AppendChildren(const TTreeNodeVect& children)
{
   for(auto itr: children)
   {
      AddChildNode(itr);
   }
}

bool TreeNode::RemoveNodeAtRow(const string& rowStr, size_t row)
{
   if((0 == row) || (CalcNestedChildCount() < row))
   {
      throw;
      return false;
   }
   TreeNode* remNode = &(*this)[row];
   if(rowStr != *(remNode->mp_nodeNameStrPtr))
   {
      return false;
   }
//   TreeNode* parentNode = remNode->mp_parentNode;
   // This would be better with a list, but we need random access
   TTreeNodeVect& childVect =
         (nullptr != remNode->mp_parentNode ?
               remNode->mp_parentNode->m_children : m_children);
   TTreeNodeVect newVect;
   for(auto itr: childVect)
   {
      if(remNode->mp_nodeNameStrPtr != itr.mp_nodeNameStrPtr)
      {
         newVect.push_back(itr);
      }
      else
      {
         for(auto itr2: remNode->m_children)
         {
            newVect.push_back(itr2);
         }
      }
   }
   m_children = newVect;
   return true;
}

void TreeNode::ClearAllChildren()
{
   m_children.clear();
}

const string kDateStr("date");
const string kTimeStr("time");
const string kExpandStr("expand");
const string kUniqueIDStr("uniqueID");
const string kTrueStr("true");
const string kFalseStr("false");
const string kNotADateTimeStr("not-a-date-time");
const string kChildrenStr("children");
bool TreeNode::LoadPTree(ptree& pTree)
{
   BoostJSON bJson(pTree);
   bJson.Dump();
   for(auto objItr: bJson.getPt())
   {
      bool first(0 < objItr.first.size());
      bool childName(0 < objItr.second.data().size());
      bool children(0 < objItr.second.size());

      const string& firstStr = objItr.first;
      if(first && childName && !children)
      {
         const string str(objItr.first);
         const string value(objItr.second.data());
         if(str == kDateStr)
         {
            if(kNotADateTimeStr == value)
            {
               date tmpDate(special_values::not_a_date_time);
               m_date = tmpDate;
            }
            else
            {
               m_date = from_string(value);
            }
         }
         else if(str == kTimeStr)
         {
            if(kNotADateTimeStr == value)
            {
               ptime tmpTime(special_values::not_a_date_time);
               m_time = tmpTime;
            }
            else
            {
               m_time = boost::posix_time::time_from_string(value);
            }
         }
         else if(str == kExpandStr)
         {
             if(kTrueStr == value)
             {
                m_expanded = true;
             }
             else if (kFalseStr == value)
             {
                 m_expanded = false;
             }
             else
             {
                throw;
             }
         }
         else if(str == kUniqueIDStr)
         {
            unsigned long tmp = strtoul(value.c_str(), NULL, 0);
            m_uniqueID = strtoul(value.c_str(), NULL, 0);
            m_maxUniqueID = (m_maxUniqueID > m_uniqueID ? m_maxUniqueID : m_uniqueID + 1);
         }
         else
         {
            throw;
         }
      }
      else if (first && !childName && children)
      {
         if(kChildrenStr == objItr.first)
         {
            ptree& pt = objItr.second;
            LoadPTree(pt);
         }
         else
         {
            TreeNode node(objItr.first, this);
            ptree& pt = objItr.second;
            node.LoadPTree(pt);
            m_children.push_back(node);
         }
      }
   }
   return true;
}

void TreeNode::SetDate(date& newDate, EnumTargetNode node)
{
   switch(node)
   {
   case kParentNode:
      m_date = newDate;
      break;
   case kLastChildNode:
      m_children.back().m_date = newDate;
      break;
   default:
      throw;
   }
}

void TreeNode::SetTime(ptime& newTime, EnumTargetNode node)
{
   switch(node)
   {
   case kParentNode:
      m_time = newTime;
      break;
   case kLastChildNode:
      m_children.back().m_time = newTime;
      break;
   default:
      throw;
   }
}

void TreeNode::SetDateTime(date& newDate, ptime& newTime, EnumTargetNode node)
{
   switch(node)
   {
   case kParentNode:
      m_date = newDate;
      m_time = newTime;
      break;
   case kLastChildNode:
      m_children.back().m_date = newDate;
      m_children.back().m_time = newTime;
      break;
   default:
      throw;
   }
}

void TreeNode::SetExpandState(bool expand)
{
   m_expanded = expand;
}

bool TreeNode::ReadStrAtRow(size_t row, string& rowStr) const
{
   size_t rowCnt(row);
   if(0 == row)
   {
      rowStr = *mp_nodeNameStrPtr;
      return true;
   }
   --rowCnt;
   for(auto itr: m_children)
   {
      if (0 == rowCnt)
      {
         rowStr = *itr.mp_nodeNameStrPtr;
         return true;
      }
      size_t nestedChildCnt(itr.CalcNestedChildCount());
      if(nestedChildCnt < rowCnt)
      {
         --rowCnt;

          rowCnt -= nestedChildCnt;
      }
      else
      {
         return itr.ReadStrAtRow(rowCnt, rowStr);
      }
   }
   return false;
}

const TTreeNodeVect& TreeNode::getChildren() const
{
   return m_children;
}

const date& TreeNode::getDate() const
{
   return m_date;
}

const ptime& TreeNode::getTime() const
{
   return m_time;
}

bool TreeNode::getExpandState() const
{
   return m_expanded;
}

unsigned long TreeNode::getUniqueID() const
{
   return m_uniqueID;
}

const string* TreeNode::getMpNodeNameStrPtr() const
{
   return mp_nodeNameStrPtr;
}

const string& TreeNode::getMpNodeNameStr() const
{
   return *mp_nodeNameStrPtr;
}

void TreeNode::FormatWithBackslash(const string& inputStr,
                                   string& outputStr) const
{
   outputStr.clear();
   for(size_t i = 0; inputStr.size() > i; ++i)
   {
      if(('"' == inputStr[i])
              || ('\\' == inputStr[i])
            )
      {
         outputStr += '\\';
         outputStr += inputStr[i];
      }
      else if('\n' == inputStr[i])
      {
         outputStr += "<CR>";
      }
      else if('\t' == inputStr[i])
      {
         outputStr += "<TAB>";
      }
      else
      {
         outputStr += inputStr[i];
      }
   }
}

void TreeNode::SetEqualTo(const TreeNode& rhs)
{
   mp_parentNode     = rhs.mp_parentNode;
   mp_nodeNameStrPtr = rhs.mp_nodeNameStrPtr;
   m_date            = rhs.m_date;
   m_time            = rhs.m_time;
   m_expanded        = rhs.m_expanded;
   m_uniqueID        = rhs.m_uniqueID;
   m_children        = rhs.m_children;
}

bool TreeNode::IsEqualTo(const TreeNode& rhs) const
{
   bool rslt(rhs.m_children.size() == m_children.size());
   if(!rslt)
   {
      return false;
   }
   for(size_t i = 0; m_children.size() > i; ++i)
   {
      rslt &= (rhs.m_children[i].IsEqualTo(m_children[i]));
   }
   return (rslt
         && (rhs.mp_parentNode == mp_parentNode)
         && (rhs.mp_nodeNameStrPtr == mp_nodeNameStrPtr)
         && (rhs.m_date == m_date)
         && (rhs.m_time == m_time)
         && (rhs.m_expanded == m_expanded)
         && (rhs.m_uniqueID == m_uniqueID));
}

const TStrSet& TreeNode::getMsItemRepoSet()
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return ms_itemRepoSet;
}

} /* namespace ZiegGTDKanban */
