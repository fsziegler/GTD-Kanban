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
#include <set>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/filesystem.hpp>
#include "BoostJSON.h"

using namespace std;
using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::filesystem;
using namespace BoostJSONDemo;

namespace ZiegGTDKanban
{

// Typedefs
typedef set<string> TStrSet;
typedef set<const string*> TCStrPtrSet;
typedef vector<string> TStrVect;

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
   TreeNode(const string& newItemStr, TreeNode* parentNode = nullptr);
   virtual ~TreeNode();
   TreeNode(const TreeNode& rhs);
   TreeNode& operator=(const TreeNode& rhs);
   bool operator==(const TreeNode& rhs);
   bool operator!=(const TreeNode& rhs);
   // operator[] treats the tree as a sequential list, and returns the index-th
   // TreeNode, or NonExistentTreeNode if index is out of range.
   TreeNode& operator[](size_t index);
   static TreeNode& getNonExistentTreeNode();

   // INFORMATIONAL
   // GetRepoSetStrPtr() returns a pointer to newItemStr in the set of added
   // item names, inserting it if it is not already there.
   static const string* GetRepoSetStrPtr(const string& newItemStr);
   // IsItemInSystem() returns true iff newItemStr is in the set of added item
   // names.
   static bool IsStrInSystem(const string& newItemStr);
   // RemoveNthChild() returns the number of TreeNode instances named itemStr,
   // returning the index of the last one found in lastIndexVect (empty if not
   // found).
   unsigned int GetNumInstancesOfItemStr(const string& itemStr,
         TNodeLocationDeque &lastIndexDeque) const;
   size_t CalcNestedChildCount() const;

   // INPUT/OUTPUT
   void IndentJSONFile(size_t indent, ofstream& jsonOutFile) const;
   void DumpAllToJSONFile(size_t indent, ofstream& jsonOutFile) const;

   // ADD/REMOVE ACTIONS
   // AddChildNode() appends childNode to this node's children, returning the
   // resulting number of children.
   TreeNode& AddChildNode(TreeNode& childNode);
   void AppendChildren(const TTreeNodeVect& children);
   bool RemoveNodeAtRow(const string& rowStr, size_t row);
   void ClearAllChildren();
   bool LoadPTree(ptree& pTree);

   // SETTERS
   void SetDate(date& newDate, EnumTargetNode node = kParentNode);
   void SetTime(ptime& newTime, EnumTargetNode node = kParentNode);
   void SetDateTime(date& newDate, ptime& newTime,
         EnumTargetNode node = kParentNode);
   void SetExpandState(bool expand);
   void AddLinkStr(const string& newLinkStr);

   // ACCESSORS
   bool ReadStrAtRow(size_t row, string& rowStr) const;
   const TTreeNodeVect& getChildren() const;
   const date& getDate() const;
   const ptime& getTime() const;
   bool getExpandState() const;
   unsigned long getUniqueID() const;
   const TStrVect& getlinksVect() const;
   const string* getMpNodeNameStrPtr() const;
   const string& getMpNodeNameStr() const;
   static const TStrSet& getMsItemRepoSet();

private:
   void FormatWithBackslash(const string& inputStr, string& outputStr) const;
   void SetEqualTo(const TreeNode& rhs);
   bool IsEqualTo(const TreeNode& rhs) const;

   // NOT IMPLEMENTED
   TreeNode();

   static TStrSet          ms_itemRepoSet;   // Set of all added user item names
   static recursive_mutex  m_mutex;          // Mutex to keep class thread safe
   static unsigned long    m_maxUniqueID;
   TreeNode*               mp_parentNode;
   const string*           mp_nodeNameStrPtr;
   date                    m_date;
   ptime                   m_time;
   bool                    m_expanded;
   unsigned long           m_uniqueID;
   TStrVect                m_linksVect;
   TTreeNodeVect           m_childrenVect;
};

} /* namespace ZiegGTDKanban */

#endif /* TREENODE_H_ */
