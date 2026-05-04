#pragma once

#include "OrderItem.h";
#include "DialougeClass.h";
#include <iostream>;
#include <string>;
#include "PlayerStats.h"
using namespace std;

class Fish : public OrderItem {
public:
	Fish()
	{
		itemName = "Fish";
		ExpNeeded = 10;
		cost = 20;
	}
	//Remember to return the rating and check accordingly!
	void prepareItem(PlayerStats* playerStats)
	{
		Dialouge diaObj;
		int passedChecks = 7; //6 checks total
		string userInp;
		//1
		string checkPhrase = "S.KI.n";
		diaObj.writeDialouge("Type this out: S.KI.n", false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("You skin the fish..", false, true);

		//2
		diaObj.writeDialouge("Type this out: C.Ut.", false, true);
		checkPhrase = "C.Ut.";
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("You cut the fish...", false, true);

		//3 
		diaObj.writeDialouge("Type this out: placeOnTray", false, true);
		checkPhrase = "placeOnTray";
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("The Fish is placed on the tray and put into the oven..", false, true);

		//4 Prof
		if (playerStats->getProf() > 25)
		{
			diaObj.writeDialouge("Proficency Skip! Item added to order tray..", true, true);
			passedChecks -= 3;
		}
		else
		{
			diaObj.writeDialouge("Type this out: W.A.it FortheFishTo.Cook...", false, true);
			checkPhrase = "W.A.it FortheFishTo.Cook...";
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("You wait as the fish is cooked in the oven... Ding!", false, true);

			//5
			diaObj.writeDialouge("Type this out: TakeOut", false, true);
			checkPhrase = "TakeOut";
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("The fish is taken out of the oven and placed on the table...", false, true);

			//6
			diaObj.writeDialouge("Type this out: Season", false, true);
			checkPhrase = "Season";
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("The Fish is seasoned and is placed on the order tray.", false, true);
		}
		int total = 100 / passedChecks;
		itemScore = total;
	}
};
