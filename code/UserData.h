/*
 File: UserData.h

 Created on: Dec 27, 2015@5:00:57 PM
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
#ifndef USERDATA_H_
#define USERDATA_H_

#include "TreeNode.h"
#include <string>
#include <map>

namespace ZiegGTDKanban
{

// Enums
enum class EnumGTDCategory
{
   kInBasket,
   kSomedayMaybe,
   kReference,
   kDoIt,
   kWaitingForAnotherPerson,
   kCalendar,
   kProjectsToPlan,
   kProjectPlans,
   kNextActions,
   kTrash,
   kMoveQueue,
   kGTDCategoryUNKNOWN,
};

// Typedefs
typedef pair<EnumGTDCategory, string> TGTDCategoryPair;
typedef map<EnumGTDCategory, string> TGTDCategoryMap;

typedef vector<const string*> TStrPtrVect;

typedef pair<EnumGTDCategory, TreeNode> TCatTreeNodeVectPair;
typedef map<EnumGTDCategory, TreeNode> TCatTreeNodeVectMap;

// Class UserData holds all of the user's GTD-Kanban data, including the
// In-Basket, GTD, and Kanban data, as well as its state.
class UserData
{
public:
   UserData();
   virtual ~UserData();

   // INFORMATIONAL
//   // ReadStrAtRow() returns the string in category at row.
   bool ReadStrAtRow(EnumGTDCategory category, size_t row,
         string& rowStr) const;
//   // GetGTDCatStr() returns the string for gtdCat.
//   const string& GetGTDCatStr(EnumGTDCategory category) const;
//   // GetCategoryItemCount() returns the number of instances of itemStr in the
//   // category.
//   int GetCategoryStrCount(EnumGTDCategory category,
//         const string& itemStr) const;
//   // FindNthCategoryItemIndex() returns true iff itemStr appears in the
//   // category at least n times, returning the index in the category iff true.
//   bool FindNthCategoryStrIndex(EnumGTDCategory category,
//         const string& itemStr, const size_t n, size_t& index) const;
   // GetNthCategoryStr() returns true iff the category contains at least
   // index items, setting itemStr to this value iff true.
   bool GetNthCategoryStr(EnumGTDCategory category, const size_t& index,
         string& itemStr) const;

   // INPUT/OUTPUT
   // DumpGTDCategory() dumps the GTD category contents to the console.
   void DumpGTDCategory(EnumGTDCategory category) const;
   // DumpAllGTD() dumps all GTD contents to the console.
   void DumpAllGTD() const;
   void DumpAllToJSONFile(const string& jsonFileNameStr) const;
   bool LoadFromJSONFile(const string& jsonFileNameStr, bool clearExisting =
         true);

   // ACCESSORS
   // getGtdFixedCatMap() returns a reference to the ms_gtdFixedCatMap data
   // member.
   static const TGTDCategoryMap& getGtdFixedCatMap();
   static EnumGTDCategory LookUpCategory(const string& categoryStr);

   // ADDING ACTIONS
   // AddItemToCategory() adds newItemStr to the category.
   size_t AddStrToCategory(const string& newItemStr, EnumGTDCategory category =
         EnumGTDCategory::kInBasket);
   // AddItemsToCategory() adds multiple items in newItemStr, delimited by
   // delim, to the category.
   size_t AddDelimStrToCategory(const string& newItemsStr,
         EnumGTDCategory category = EnumGTDCategory::kInBasket, char delim =
               '\n');

   // FINDING ACTIONS

   // MOVING ACTIONS
   // MoveNthStrBetweenCategories() moves the n-th item in the srcCat
   // category to the tgtCat category, returning false if there is no n-th
   // item or it does not match itemStr.
   bool MoveNthStrBetweenCategories(const string& itemStr,
         EnumGTDCategory srcCat, EnumGTDCategory tgtCat, size_t n);
   // MoveAllBetweenCategories() moves every item in srcCat to tgtCat.
   size_t MoveAllBetweenCategories(EnumGTDCategory srcCat,
         EnumGTDCategory tgtCat);
   const TCatTreeNodeVectMap& getGtdNodeTree() const;

   // REMOVING ACTIONS
   void Clear();

private:
   void PopulateGTDNodeTree();
   // GetCTreeNode() returns the TreeNode for category.
   TreeNode& GetTreeNode(EnumGTDCategory category);
   const TreeNode& GetCTreeNode(EnumGTDCategory category) const;
   // getCategoryCTreeNodeVect() returns the TTreeNodeVect of the children of
   // the category TreeNode.
   const TTreeNodeVect& getCategoryCTreeNodeVect(
         EnumGTDCategory category) const;
   const string& GetNodeNameStr(const TTreeNodeVect& treeNodeVect,
         size_t index) const;
   void PopulateCStrPtrSetFromTreeNode(const TreeNode& treeNode,
         TCStrPtrSet& strPtrSet) const;
   void DumpIndent(int indent) const;
   void DumpTreeNode(const TreeNode& treeNode, int& cnt, int indent = 0) const;

   // NOT IMPLEMENTED
   UserData(const UserData&);
   UserData& operator=(const UserData&);
   bool operator==(const UserData&);
   bool operator!=(const UserData&);

   static TGTDCategoryMap  ms_gtdFixedCatMap;   // Fixed map of category
                                                // enum-string pairs
   static recursive_mutex  m_mutex;          // Mutex to keep class thread safe
   TCatTreeNodeVectMap     m_gtdNodeTree;    // Tree of structured GTD items
};

} /* namespace ZiegGTDKanban */

#endif /* USERDATA_H_ */
