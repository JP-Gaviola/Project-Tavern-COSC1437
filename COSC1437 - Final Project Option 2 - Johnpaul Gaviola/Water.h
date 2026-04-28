#pragma once

#include "OrderItem.h";
#include "DialougeClass.h";
#include <iostream>;
#include <string>;
using namespace std;

class Water : public OrderItem {
public:
	//Remember to return the rating and check accordingly!
	int prepareItem()
	{
		cout << "Water time yo..." << endl;
		return 5;
	}
};