#pragma once
#include "Customer.h"
#include <string>
#include "Water.h"
#include "Bread.h"
using namespace std;

class SuperHighResident : public Customer {

public:
	SuperHighResident()
	{
		//Set stats here
		customerName = "Super High Town Resident";
		patienceLevel = 90; //Allowed ellapsed time without penalty 
		budget = 100; //max amount of money to be ordered 
		minRep = 45; //Minimum rep to accept order 
		rowdiness = 20; //Grade req increase

		prefSize = 2; //Pref size
		pref = new string[prefSize]{ "Ham", "Fish" }; //Prefered Items 
		onlyPref = false; //Limit order to preferences only 

		//First walk into store
		Denter = "Now this is more like it ...";
		//Order declined
		Ddeclined = "What is your problem??!?";
		//Took order
		DstartOrder = "I'd like to order only the finest of this empire's:";
		//Submitted food to customer
		DsubmitOrder = "Hmmm...";
		//Ratings
		DOrderGood = "Tastes absolutely amazing!";
		DOrderBad = "Tasted terrible what is this?!?!";
		//Wait time / rep 
		DWaitToLong = "Could be a bit more faster though...";
		DrepTooLow = "This place is not up to my standards sorry.";
	}
	~SuperHighResident()
	{
		delete[] pref;
	}
};