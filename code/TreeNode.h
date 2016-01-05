/*
 File: TreeNode.h

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
#ifndef TREENODE_H_
#define TREENODE_H_

#include <vector>
#include <deque>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

namespace ZiegGTDKanban
{

class TreeNode;
typedef vector<TreeNode> TTreeNodeVect;

enum EnumTargetNode
{
   kParentNode,
   kLastChildNode,
};

typedef deque<size_t> TNodeLocationDeque;

class TreeNode
{
public:
   TreeNode();
   TreeNode(const string& newItemStr, TreeNode* parentNode = nullptr);
   virtual ~TreeNode();
   TreeNode(const TreeNode& rhs);
   TreeNode& operator=(const TreeNode& rhs);
   // operator[] treats the tree as a sequential list, and returns the index-th
   // TreeNode, or NonExistentTreeNode if index is out of range.
   TreeNode& operator[](size_t index);

   static TreeNode NonExistentTreeNode;

   // INFORMATIONAL
   // RemoveNthChild() returns the number of TreeNode instances named itemStr,
   // returning the index of the last one found in lastIndexVect (empty if not
   // found).
   unsigned int GetNumInstancesOfItemStr(const string& itemStr,
         TNodeLocationDeque &lastIndexDeque) const;
   size_t CalcNestedChildCount() const;
   bool ReadStrAtRow(size_t row, string& rowStr) const;
   size_t CalcChildrenCountUnderRow(size_t row);

   // ADD/REMOVE ACTIONS
   // AddChildNode() appends childNode to this node's children, returning the
   // resulting number of children.
   size_t AddChildNode(TreeNode& childNode);
   // RemoveNthChild() removes the n-th child node, iff extant, returning the
   // operation result.
   bool RemoveNthChild(size_t n);
   bool RemoveNodeAtRow(const string& rowStr, size_t row);
   bool RemoveIndexedChild(TNodeLocationDeque &indexDeque);
   // FindNextItem() appends the path to the next child named itemStr to
   // indexVect, iff extant, where indexVect may be empty or contain a path to a
   // sub-node.
   bool FindNextItem(const string& itemStr, TNodeLocationDeque &indexDeque);

   // SETTERS
   void SetDate(date& newDate, EnumTargetNode node = kParentNode);
   void SetTime(ptime& newTime, EnumTargetNode node = kParentNode);
   void SetDateTime(date& newDate, ptime& newTime,
         EnumTargetNode node = kParentNode);

   // GETTERS
   const TTreeNodeVect& getChildren() const;
   const date& getDate() const;
   const ptime& getTime() const;
   const string* getMpNodeNameStrPtr() const;
   const string& getMpNodeNameStr() const;

private:
   TreeNode* FindItem(const TNodeLocationDeque &indexDeque);
   void SetEqualTo(const TreeNode& rhs);

   TreeNode*      mp_parentNode;
   const string*  mp_nodeNameStrPtr;
   date           m_date;
   ptime          m_time;
   TTreeNodeVect  m_children;

   // NOT IMPLEMENTED
   bool operator==(const TreeNode&);
   bool operator!=(const TreeNode&);
};

} /* namespace ZiegGTDKanban */

#endif /* TREENODE_H_ */
