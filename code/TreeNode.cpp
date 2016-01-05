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
#include <TreeNode.h>
#include <boost/thread/lock_guard.hpp>

namespace ZiegGTDKanban
{

TStrSet           TreeNode::ms_itemRepoSet;
recursive_mutex   TreeNode::m_mutex;

TreeNode NonExistentTreeNode("NonExistentTreeNode");

TreeNode::TreeNode(const string& newItemStr, TreeNode* parentNode)
:mp_parentNode(parentNode),
 mp_nodeNameStrPtr(GetRepoSetStrPtr(newItemStr)),
m_date(special_values::not_a_date_time),
m_time(special_values::not_a_date_time)
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

size_t TreeNode::AddChildNode(TreeNode& childNode)
{
   m_children.push_back(childNode);
   return m_children.size();
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

const string* TreeNode::getMpNodeNameStrPtr() const
{
   return mp_nodeNameStrPtr;
}

const string& TreeNode::getMpNodeNameStr() const
{
   return *mp_nodeNameStrPtr;
}

void TreeNode::SetEqualTo(const TreeNode& rhs)
{
   mp_parentNode     =  rhs.mp_parentNode;
   mp_nodeNameStrPtr =  rhs.mp_nodeNameStrPtr;
   m_date            =  rhs.m_date;
   m_time            =  rhs.m_time;
   m_children        =  rhs.m_children;
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
         && (rhs.m_time == m_time));
}

const TStrSet& TreeNode::getMsItemRepoSet()
{
   lock_guard<recursive_mutex> guard(m_mutex);
   return ms_itemRepoSet;
}

} /* namespace ZiegGTDKanban */
