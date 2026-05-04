#pragma once
#include "Customer.h"
#include <string>
#include "Water.h"
#include "Bread.h"
using namespace std;

class TownResident : public Customer {

public:
	TownResident()
	{
		//Set stats here
		customerName = "Town Resident";
		patienceLevel = 60; //Allowed ellapsed time without penalty 
		budget = 20; //max amount of money to be ordered 
		minRep = -999; //Minimum rep to accept order 

		prefSize = 2; //Pref size
		pref = new string[prefSize]{ "Water", "Bread" }; //Prefered Items 
		onlyPref = false; //Limit order to preferences only 

		//First walk into store
		Denter = "Hello, what a nice place this is! Here for my usual...";
		//Order declined
		Ddeclined = "Oh.. ";
		//Took order
		DstartOrder = "Alright as always: ";
		//Submitted food to customer
		DsubmitOrder = "Hmm..";
		//Ratings
		DOrderGood = "Looks great!";
		DOrderBad = "Could be better,..";
		//Wait time / rep 
		DWaitToLong = "Took a while though...";
		DrepTooLow = "Son";
	}
	~TownResident()
	{
		delete[] pref;
	}
};