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

namespace ZiegGTDKanban
{

TreeNode TreeNode::NonExistentTreeNode("NonExistentTreeNode");

TreeNode::TreeNode()
:mp_nodeNameStrPtr(nullptr),
m_date(special_values::not_a_date_time),
m_time(special_values::not_a_date_time)
{
}

TreeNode::TreeNode(const string& newItemStr, TreeNode* parentNode)
:mp_parentNode(parentNode),
 mp_nodeNameStrPtr(&newItemStr),
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

size_t TreeNode::CalcChildrenCountUnderRow(size_t row)
{
   const TreeNode& rowNode = (*this)[row];
   size_t cnt(rowNode.m_children.size());
   for(auto itr: rowNode.m_children)
   {
      cnt += itr.CalcNestedChildCount();
   }
   return cnt;
}

size_t TreeNode::AddChildNode(TreeNode& childNode)
{
   m_children.push_back(childNode);
   return m_children.size();
}

bool TreeNode::RemoveNthChild(size_t n)
{
   if(m_children.size() > n)
   {
      for (size_t i = n; m_children.size() > i; ++i)
      {
         m_children[i] = m_children[i + 1];
      }
      m_children.pop_back();
      return true;
   }
   return false;
}

TreeNode* TreeNode::FindItem(const TNodeLocationDeque &indexDeque)
{
   // Case of this node
   if(0 == indexDeque.size())
   {
      return this;
   }
   const size_t childIndex(indexDeque[0]);
   // Error handling - should not happen
   if((0 < childIndex) && (m_children.size() < childIndex))
   {
      return nullptr;
   }
   // Case where item is a child node of this
   if(1 == indexDeque.size())
   {
      // We know this is not nullptr due to error handling above
      return &(*this)[childIndex];
   }

   // Case of needing to iterate down further
   TNodeLocationDeque newDeque(indexDeque);
   newDeque.pop_front();
   return (*this)[childIndex].FindItem(newDeque);
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
   size_t sz1(m_children.size());
   m_children = newVect;
   size_t sz2(m_children.size());
   return true;
}

bool TreeNode::FindNextItem(const string& itemStr,
      TNodeLocationDeque &indexDeque)
{
   // Find the location passed in, if any
   if(0 < indexDeque.size())
   {
      // Search for itemStr under the TreeNode in indexVect
      TreeNode* itr = FindItem(indexDeque);
      if(nullptr == itr)
      {
         return false;
      }
      TNodeLocationDeque tmpVect;
      if(itr->FindNextItem(itemStr, tmpVect))
      {
         for(auto tmpItr: tmpVect)
         {
            indexDeque.push_back(tmpVect[tmpItr]);
         }
         return true;
      }
      return false;
   }

   // Case of this node matching
   if(0 == itemStr.compare(*mp_nodeNameStrPtr))
   {
      indexDeque.push_back(0);
      return true;
   }

   // Search children for a match
   size_t cnt(1);
   while(m_children.size() >= cnt)
   {
      // Case of root child node matching
      if (0 == (*m_children[cnt - 1].mp_nodeNameStrPtr).compare(
            *mp_nodeNameStrPtr))
      {
         indexDeque.push_back(cnt);
         return true;
      }
      // Case of child of child node matching
      if(m_children[cnt - 1].FindNextItem(itemStr, indexDeque))
      {
         return true;
      }
      ++cnt;
   }
   return false;
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

} /* namespace ZiegGTDKanban */
