#pragma once
#include "Customer.h"
#include <string>
using namespace std;

class Ingis : public Customer {
public:
	Ingis()
	{
		//Set stats here
		customerName = "ingis";
		patienceLevel = 60; //Allowed ellapsed time without penalty 
		budget = 20; //max amount of money to be ordered 
		minRep = -999; //Minimum rep to accept order 

		prefSize = 1; //Pref size
		pref = new string[prefSize]{"Bread"}; //Prefered Items 
		onlyPref = true; //Limit order to preferences only 

		//First walk into store
		Denter = "Hi sorry, I'm a starving Victorian child but I have no money. Are you able to spare just bread, bitte? :(";
		//Order declined
		Ddeclined = "It's okay, haha... thanks for considering.............................. :(";
		//Took order
		DstartOrder = "OMG!!!!!!!!,!!,!!.!!.! [shark smiling picture] thank you thank you thank you \n Take your time, just:";
		//Submitted food to customer
		DsubmitOrder = "YAY!!!!.!.!,!!.!!!!!!!!.!!!,!!! Okay, let's see!";
		//Ratings
		DOrderGood = "Wow this is like such bread it's so bread. Thank you!!!";
		DOrderBad = "Wow this is kind of bad but bread is bread! Thank you!!!";
		//Wait time / rep 
		DWaitToLong = "Kind of took a while but yay!!! Bread is bread!!!!";
		DrepTooLow = "Son";

	}
	~Ingis()
	{
		delete[] pref;
	}

};