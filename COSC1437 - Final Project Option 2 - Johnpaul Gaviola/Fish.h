#pragma once

#include "OrderItem.h";
#include "DialougeClass.h";
#include <iostream>;
#include <string>;
using namespace std;

class Fish : public OrderItem {
public:
	Fish()
	{
		itemName = "Fish";
		ExpNeeded = 10;
		cost = 10;
	}
	//Remember to return the rating and check accordingly!
	void prepareItem()
	{
		Dialouge diaObj;
		cout << "Water time yo..." << endl;
		itemScore =  5;
	}
};
