#pragma once
#include <string>
using namespace std;

//Can be a drink or food 
class OrderItem {

protected:
	string itemName; //Name of item used to check if it was in the order
	int itemScore;
	int stock;
	int ExpNeeded;
	int cost;

public:
	virtual void prepareItem() = 0; //override this 

	int getItemScore();
	int getStock();
	string getName();
	int getExpNeeded();
	int getCost();


	void setItemScore(int);
	void setStock(int);
	//Code the custom minigame here and return a score to be graded 
};