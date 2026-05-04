#pragma once

#include "OrderItem.h";
#include "DialougeClass.h";
#include <iostream>;
#include <string>;
#include "PlayerStats.h"
using namespace std;

class Bread : public OrderItem {
public:
	Bread()
	{
		itemName = "Bread";
		ExpNeeded = 0;
		cost = 5;
	}
	//Remember to return the rating and check accordingly!
	void prepareItem(PlayerStats* playerStats)
	{
		Dialouge diaObj;
		int passedChecks = 5; //4 checks total
		string userInp;
		//1
		string checkPhrase = "B.R.E.A.D.";
		diaObj.writeDialouge("Type this out: B.R.E.A.D.", false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("The dough powder is mixed...", false, true);

		//2
		diaObj.writeDialouge("Type this out: W.A.T.E.R!", false, true);
		checkPhrase = "W.A.T.E.R!";
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("The dough mixture is finalized with the addition of water...", false, true);

		//3 Prof
		if (playerStats->getProf() > 10)
		{
			diaObj.writeDialouge("Proficency Skip! Item added to order tray..", true, true);
			passedChecks -= 2;
		}
		else
		{
			diaObj.writeDialouge("Type this out: ThrowThis Bread inTheOven RightNow and CookItyeahYeah!", false, true);
			checkPhrase = "ThrowThis Bread inTheOven RightNow and CookItyeahYeah!";
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("The dough is placed into the oven and cooked...", false, true);

			//4
			diaObj.writeDialouge("Type this out: W.A.I.T.", false, true);
			checkPhrase = "W.A.I.T.";
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}

			diaObj.writeDialouge("Ding!", false, true);
			diaObj.writeDialouge("The bread is taken out of the oven and placed on the order tray.", false, true);
		}
		int total = 100 / passedChecks;
		itemScore = total;
	}
};