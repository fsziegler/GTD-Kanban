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

TreeNode::TreeNode()
:mp_nodeNameStrPtr(nullptr),
m_date(special_values::not_a_date_time),
m_time(special_values::not_a_date_time)
{
}

TreeNode::TreeNode(const string& newItemStr)
:mp_nodeNameStrPtr(&newItemStr),
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

size_t TreeNode::AddChildNode(TreeNode& childNode)
{
   m_children.push_back(childNode);
   return m_children.size();
}

size_t TreeNode::RemoveNthChild(size_t n)
{
   for (size_t i = n; m_children.size() > i; ++i)

   {
      m_children[i] = m_children[i + 1];
   }
   m_children.pop_back();
   return m_children.size();
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

void TreeNode::SetEqualTo(const TreeNode& rhs)
{
   mp_nodeNameStrPtr = rhs.mp_nodeNameStrPtr;
   m_date = rhs.m_date;
   m_time = rhs.m_time;
   m_children = rhs.m_children;
}

} /* namespace ZiegGTDKanban */
