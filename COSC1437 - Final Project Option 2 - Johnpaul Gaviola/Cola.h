#pragma once

#include "OrderItem.h"
#include "DialougeClass.h"
#include <iostream>
#include <string>
#include "PlayerStats.h"
using namespace std;

class Cola : public OrderItem {
public:
	Cola()
	{
		itemName = "Cola";
		ExpNeeded = 0;
		cost = 5;
	}
	//Remember to return the rating and check accordingly!
	void prepareItem(PlayerStats* playerStats)
	{
		Dialouge diaObj;
		int passedChecks = 3; //2 checks total
		string userInp;
		//1
		string checkPhrase = "CUP";
		diaObj.writeDialouge("Type this out: CUP", false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("A cup is grabbed..", false, true);

		//2
		diaObj.writeDialouge("Type this out: pouringVeryFizzyColaaaa z.z.z.z", false, true);
		checkPhrase = "pouringVeryFizzyColaaaa z.z.z.z";
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("Cola is poured into the cup and placed on the order tray.", false, true);

		int total = 100 / passedChecks;
		itemScore = total;
	}
};