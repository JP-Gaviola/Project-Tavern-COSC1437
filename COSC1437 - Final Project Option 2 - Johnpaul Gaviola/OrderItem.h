#pragma once
#include <string>
using namespace std;

//Can be a drink or food 
class OrderItem {

protected:
	string itemName; //Name of item used to check if it was in the order
	int itemScore = 100; //Set to 100 by default for grading
	int stock;
	int ExpNeeded;
	int cost;

public:
	//Code the custom minigame here
	virtual void prepareItem() = 0; //override this 
	
	int getItemScore();
	int getStock();
	string getName();
	int getExpNeeded();
	int getCost();


	void setItemScore(int);
	void setStock(int);

};