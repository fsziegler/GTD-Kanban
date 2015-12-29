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
