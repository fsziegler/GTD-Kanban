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

class TreeNode
{
public:
   TreeNode();
   TreeNode(const string& newItemStr);
   virtual ~TreeNode();
   TreeNode(const TreeNode& rhs);
   TreeNode& operator=(const TreeNode& rhs);

   size_t AddChildNode(TreeNode& childNode);
   size_t RemoveNthChild(size_t n);
   void SetDate(date& newDate, EnumTargetNode node = kParentNode);
   void SetTime(ptime& newTime, EnumTargetNode node = kParentNode);
   void SetDateTime(date& newDate, ptime& newTime,
         EnumTargetNode node = kParentNode);

   const TTreeNodeVect& getChildren() const;
   const date& getDate() const;
   const ptime& getTime() const;
   const string* getMpNodeNameStrPtr() const;

private:
   void SetEqualTo(const TreeNode& rhs);
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
