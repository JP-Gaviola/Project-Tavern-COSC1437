#pragma once

#include "OrderItem.h"
#include "DialougeClass.h"
#include <iostream>
#include <string>
using namespace std;

class Water : public OrderItem {
public:
	Water()
	{
		itemName = "Water";
		ExpNeeded = 0;
		cost = 1;
	}
	//Remember to return the rating and check accordingly!
	void prepareItem()
	{
		Dialouge diaObj;
		int passedChecks = 3; //2 checks total
		string userInp;
		string checkPhrase = "CUP";
		diaObj.writeDialouge("Type this out: CUP", false, true);
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("A cup is grabbed..", false, true);

		diaObj.writeDialouge("Type this out: pour water", false, true);
		checkPhrase = "pour water";
		diaObj.askUserChoice(userInp);
		if (userInp == checkPhrase)
		{
			passedChecks--;
		}
		diaObj.writeDialouge("Water is poured into the cup and placed on the order tray.", false, true);

		int total = 100 / passedChecks;
		itemScore = total;
	}
};