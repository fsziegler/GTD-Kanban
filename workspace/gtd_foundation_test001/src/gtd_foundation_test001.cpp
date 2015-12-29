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
      "software on the Web.\nGet new staff person on board August\nvacation "
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
   data.AddItemsToInBasket(inBasketStr);
   data.DumpInBasket();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

/*
   vector<string> strList;

   strList.push_back("When");
   strList.push_back("you");
   strList.push_back("try");
   strList.push_back("to");
   strList.push_back("use");
   strList.push_back("GDB's");
   strList.push_back("print");
   strList.push_back("command");
   strList.push_back("to");
   strList.push_back("display");
   strList.push_back("the");
   strList.push_back("contents");
   strList.push_back("of");
   strList.push_back("a");
   strList.push_back("vector,");
   strList.push_back("a");
   strList.push_back("stack,");
   strList.push_back("or");
   strList.push_back("any");
   strList.push_back("other");
   strList.push_back("GDB");
   strList.push_back("abstract");
   strList.push_back("data");
   strList.push_back("structure,");
   strList.push_back("you");
   strList.push_back("will");
   strList.push_back("get");
   strList.push_back("useless");
   strList.push_back("results.");
   strList.push_back("Instead,");
   strList.push_back("download");
   strList.push_back("and");
   strList.push_back("install");
   strList.push_back("one");
   strList.push_back("of");
   strList.push_back("following");
   strList.push_back("tools");
   strList.push_back("to");
   strList.push_back("properly");
   strList.push_back("view");
   strList.push_back("the");
   strList.push_back("contents");
   strList.push_back("of");
   strList.push_back("STL");
   strList.push_back("containers");
   strList.push_back("from");
   strList.push_back("within");
   strList.push_back("GDB.");

   string str;
   for(auto itr = strList.begin(); strList.end() != itr; ++itr)
   {
      cout << (*itr) << " ";
      str.append(*itr).append(" ");
   }
*/
