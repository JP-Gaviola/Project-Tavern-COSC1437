#pragma once
#include <string>
#include <iostream>
#include "OrderItem.h"
#include "GameStats.h";
#include "PlayerStats.h";

using namespace std; 

class TavernMain {
	//Code events here maybe ...
public:
	//Construtors depending on new game / loaded game 
	TavernMain();
	TavernMain(string filename);
	~TavernMain();

	int GAMESTART(); //returns ending result, one result is the intermission where players can save/exit/continue 
	void createOrder(); //Parameter should be the customer reference
	int submitOrder(); //returns a rating, submits current order
	int calcMoney(int ratingIn); //Takes a rating and calculates the earnings with tips, adds it to the day

	OrderItem getOrder();
	OrderItem getOrderAt(int);
	OrderItem getCustomerOrder();
	OrderItem getCustomerOrderAt(int);
	int getcurrOrderSize();
	int getCustOrdersize();

private:
	OrderItem* currentOrder;
	OrderItem* currCustomerOrder;
	int currSize;
	int CustOrderSize;

};