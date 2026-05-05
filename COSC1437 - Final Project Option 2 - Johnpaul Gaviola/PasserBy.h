#pragma once
#include "Customer.h"
#include <string>
#include "Water.h"
#include "Bread.h"
using namespace std;

class PasserBy : public Customer {

public:
	PasserBy()
	{
		//Set stats here
		customerName = "Passing Adventurer";
		patienceLevel = 30; //Allowed ellapsed time without penalty 
		budget = 50; //max amount of money to be ordered 
		minRep = 30; //Minimum rep to accept order 
		rowdiness = 10; //Grade req increase

		prefSize = 3; //Pref size
		pref = new string[prefSize]{ "Water", "Water", "Bread"}; //Prefered Items 
		onlyPref = false; //Limit order to preferences only 

		//First walk into store
		Denter = "Look im in a rush... Sorry";
		//Order declined
		Ddeclined = "Gosh..";
		//Took order
		DstartOrder = "I'll need these, make it quick please:";
		//Submitted food to customer
		DsubmitOrder = "Alright..";
		//Ratings
		DOrderGood = "Thanks a ton!";
		DOrderBad = "Are you trying to sabatoge my quest??";
		//Wait time / rep 
		DWaitToLong = "I'll need this faster next time..";
		DrepTooLow = "I don't really trust this tavern sorry.";
	}
	~PasserBy()
	{
		delete[] pref;
	}
};