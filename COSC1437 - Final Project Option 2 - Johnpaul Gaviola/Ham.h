#pragma once

#include "OrderItem.h";
#include "DialougeClass.h";
#include <iostream>;
#include <string>;
#include "PlayerStats.h"
using namespace std;

class Ham : public OrderItem {
public:
	Ham()
	{
		itemName = "Ham";
		ExpNeeded = 25;
		cost = 15;
	}
	//Remember to return the rating and check accordingly!
	void prepareItem(PlayerStats* playerStats)
	{
		Dialouge diaObj;
		int passedChecks = 7; //6 checks total
		string userInp;
		//1
		string checkPhrase = "A.T.T.A.C.K.";
		diaObj.writeDialouge("Type this out: " + checkPhrase, false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("The animal is attacked...", false, true);

		//2
		checkPhrase = "Cut and prepare...";
		diaObj.writeDialouge("Type this out: " + checkPhrase, false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("The animal is cut and prepared..", false, true);

		//3
		checkPhrase = "Marinate the meat and thenLikeMaybe season it a bit you know";
		diaObj.writeDialouge("Type this out: " + checkPhrase, false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("The meat is marinated and seasoned to be made out like that of ham..", false, true);

		//4 Prof
		if (playerStats->getProf() > 10)
		{
			diaObj.writeDialouge("Proficency Skip! Item added to order tray..", true, true);
			passedChecks -= 3;
		}
		else
		{
			checkPhrase = "O.V.E.N.";
			diaObj.writeDialouge("Type this out: " + checkPhrase, false, true);
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("The meat is placed inside of the oven", false, true);

			//5
			checkPhrase = "W.A.I.T.";
			diaObj.writeDialouge("Type this out: " + checkPhrase, false, true);
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("You wait for the ham to be cooked...", false, true);
			diaObj.writeDialouge("Ding!", false, true);

			//6
			checkPhrase = "Take Out OF ov3n";
			diaObj.writeDialouge("Type this out: " + checkPhrase, false, true);
			diaObj.askUserChoice(userInp);
			if (userInp == checkPhrase)
			{
				passedChecks--;
			}
			diaObj.writeDialouge("The ham is taken out of the oven and placed on the order tray.", false, true);
		}

		int total = 100 / passedChecks;
		itemScore = total;
	}
};