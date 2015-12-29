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

#include <string>
#include <vector>
#include <map>
#include <set>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/mutex.hpp>
//#include <boost/property_tree/ptree.hpp>

using namespace std;
using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;

namespace ZiegGTDKanban
{

// Enums
enum class EnumGTDCategory
{
   kInBasket,
   kSomedayMaybe,
   kReference,
   kWaitingForAnotherPerson,
   kCalendar,
   kProjectsToPlan,
   kProjectPlans,
   kNextActions,
   kGTDCategoryUNKNOWN,
};

// Typedefs
typedef pair<EnumGTDCategory, string> TGTDCategoryPair;
typedef map<EnumGTDCategory, string> TGTDCategoryMap;

typedef vector<const string*> TStrPtrVect;

typedef set<string> TStrSet;
typedef set<const string*> TCStrPtrSet;

struct TreeNode;

typedef vector<TreeNode> TTreeNodeVect;
struct TreeNode
{
   const string*  mp_nodeNameStrPtr;
   date           m_date;
   ptime          m_time;
   TTreeNodeVect  m_children;
};

typedef vector<TreeNode> TTreeNodeVect;
typedef pair<EnumGTDCategory, TTreeNodeVect> TCatTreeNodeVectPair;
typedef map<EnumGTDCategory, TTreeNodeVect> TCatTreeNodeVectMap;

// Class UserData holds all of the user's GTD-Kanban data, including the
// In-Basket, GTD, and Kanban data, as well as its state.
class UserData
{
public:
   UserData();
   virtual ~UserData();

   // INFORMATIONAL
   // GetGTDCatStr() returns the string for gtdCat.
   const string& GetGTDCatStr(EnumGTDCategory category) const;
   // GetRepoSetStrPtr() returns a pointer to newItemStr in the set of added
   // item names, inserting it if it is not already there.
   const string* GetRepoSetStrPtr(const string& newItemStr) const;
   // IsItemInSystem() returns true iff newItemStr is in the set of added item
   // names.
   bool IsItemInSystem(const string& newItemStr) const;
   // GetItemCountInBasket() returns the number of instances of itemStr in the
   // in-basket.
   int GetItemCountInBasket(const string& itemStr) const;
   // FindNthInBasketItem() returns true iff itemStr appears in the in-basket at
   // least n times, returning the index in m_inBasketVect iff true.
   bool FindNthInBasketItem(const string& itemStr, const size_t n,
         size_t& index) const;
   void DumpInBasket() const;
   void DumpGTDCategory(EnumGTDCategory category) const;
   void DumpAllGTD() const;

   // ACCESSORS
   const TStrPtrVect& getInBasketVect() const;
   const TCatTreeNodeVectMap& getGtdNodeTree() const;
   const TTreeNodeVect& GetCTreeNodeVect(EnumGTDCategory category) const;

   // ACTIONS
   // AddItemToInBasket() adds newItemStr to the in-basket.
   void AddItemToInBasket(const string& newItemStr);
   void AddItemsToInBasket(const string& newItemsStr, char delim = '\n');
   // MoveNthInBasketItemToGTD() moves the n-th itemStr in the In-basket to the
   // category, returning false if there is no n-th itemStr.
   bool MoveNthInBasketItemToGTD(const string& itemStr,
         EnumGTDCategory category, size_t n = 0);
   // This version of MoveNthInBasketItemToGTD() sets the date of the n-th
   // itemStr, and moves it into the Calendar category by default.
   bool MoveNthInBasketItemToGTD(const string& itemStr, const date& newDate,
         EnumGTDCategory category = EnumGTDCategory::kCalendar, size_t n = 0);
   // This version of MoveNthInBasketItemToGTD() sets the date and time of the
   // n-th itemStr, and moves it into the Calendar category by default.
   bool MoveNthInBasketItemToGTD(const string& itemStr, const date& newDate,
         const ptime& newTime, EnumGTDCategory category =
               EnumGTDCategory::kCalendar, size_t n = 0);

private:
   void InitNode(const string& itemStr, TreeNode& node) const;
   TTreeNodeVect& GetTreeNodeVect(EnumGTDCategory category);
   void PopulateCStrPtrSetFromTreeNode(const TreeNode& treeNode,
         TCStrPtrSet& strPtrSet) const;
   void DumpIndent(int indent) const;
   void DumpTreeNode(const TreeNode& treeNode, int indent = 0) const;
   size_t CleanUpRepoSet();

   UserData(const UserData&);
   UserData& operator=(const UserData&);
   bool operator==(const UserData&);
   bool operator!=(const UserData&);

   static TGTDCategoryMap  ms_gtdFixedCatMap;   // Fixed map of category
                                                // enum-string pairs
   static TStrSet       ms_itemRepoSet;   // Set of all added user item names
   TStrPtrVect          m_inBasketVect;   // In-basket collection
   TCatTreeNodeVectMap  m_gtdNodeTree;    // Tree of structured GTD items
   static mutex         m_mutex;
};

} /* namespace ZiegGTDKanban */

#endif /* USERDATA_H_ */
