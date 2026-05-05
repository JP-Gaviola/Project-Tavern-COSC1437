#pragma once
#include "Customer.h"
#include <string>
#include "Water.h"
#include "Bread.h"
using namespace std;

class HigherResident : public Customer {

public:
	HigherResident()
	{
		//Set stats here
		customerName = "High Town Resident";
		patienceLevel = 90; //Allowed ellapsed time without penalty 
		budget = 50; //max amount of money to be ordered 
		minRep = 35; //Minimum rep to accept order 
		rowdiness = 15; //Grade req increase

		prefSize = 2; //Pref size
		pref = new string[prefSize]{ "Water", "Fish" }; //Prefered Items 
		onlyPref = false; //Limit order to preferences only 

		//First walk into store
		Denter = "My my what a tavern!";
		//Order declined
		Ddeclined = "Oh Alright..";
		//Took order
		DstartOrder = "I'd like to have the finest:";
		//Submitted food to customer
		DsubmitOrder = "Hmm... It could look a but more apetizing but...";
		//Ratings
		DOrderGood = "Tastes amazing!!!";
		DOrderBad = "Tasted horrible!";
		//Wait time / rep 
		DWaitToLong = "Took a while though...";
		DrepTooLow = "I'm just looking around,, not sure if I want to order here yet..";
	}
	~HigherResident()
	{
		delete[] pref;
	}
};