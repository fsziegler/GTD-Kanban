//============================================================================
// Name        : gtd_foundation_test001.cpp
// Author      : Fred Ziegler
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "UserData.h"
#include <iostream>
#include <string>
#include <vector>
//#include <QDate>

using namespace std;
using namespace ZiegGTDKanban;

const string inBasketStr("Call Fred re tel. # for the garage he recommended.\n"
      "Draft thoughts for the budget-meeting agenda.\nTalk to Angela about "
      "the filing system we need to set up.\nResearch database-management "
      "software on the Web.\nGet new staff person on board\nAugust vacation\n"
      "Staff off-site retreat\nPublish book\nFinalize computer upgrades\n"
      "Update will\nFinalize budgets\nFinalize new product line\nGet "
      "comfortable with new contact-management software\nGet reprints of "
      "Fortune article\nGet a publicist\nFinish new orchard planting\nR&D "
      "joint-venture video project\nProduce new training compact disk\n"
      "Establish next year’s seminar schedule\nOrchestrate a one-hour "
      "keynote presentation\nGet proficient with videoconferencing access\n"
      "Finalize employment agreements\nInstall new backyard lights");

int main() {
   UserData data;
//   data.DumpAllToJSONFile(string("test.json"));
   data.AddDelimStrToCategory(inBasketStr);
   cout << "1. data.DumpInBasket()" << endl;
   data.DumpGTDCategory(EnumGTDCategory::kInBasket);
   int cnt(2);
   string str;
   while (data.GetNthCategoryStr(EnumGTDCategory::kInBasket, cnt, str))
   {
      if(data.MoveNthStrBetweenCategories(str, EnumGTDCategory::kInBasket,
            EnumGTDCategory::kSomedayMaybe, cnt))
      {
         ++cnt;
      }
      else
      {
         cnt = 0;
      }
      data.DumpAllGTD();
   }
   data.DumpAllToJSONFile(string("test.json"));
   cout << "2. data.DumpAllGTD()" << endl;
//   data.DumpAllGTD();
//   for(auto itr: UserData::getGtdFixedCatMap())
//   {
//      if(data.GetNthCategoryStr(EnumGTDCategory::kInBasket, 0, str))
//      {
//         data.MoveNthStrBetweenCategories(str, EnumGTDCategory::kInBasket,
//               itr.first, 1);
//      }
//   }
//   cout << "3. data.DumpAllGTD()" << endl;
//   data.DumpAllGTD();
   cout << "Done!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
