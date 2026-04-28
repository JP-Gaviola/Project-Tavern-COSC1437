#pragma once
#include <string>
using namespace std;

//Can be a drink or food 
class OrderItem {

protected:
	string itemtype; //Either a food or drink 
	string itemName; //Name of item used to check if it was in the order
	int itemScore;
	int stock;

public:
	virtual int prepareItem() = 0; //override this 

	int getItemScore();
	int getStock();
	string getType();
	string getName();


	void setType(string);
	void setName(string);
	void setItemScore(int);
	void setStock(int);
	//Code the custom minigame here and return a score to be graded 
};