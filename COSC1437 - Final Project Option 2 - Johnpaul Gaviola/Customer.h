#pragma once
#include <string>
using namespace std;

class Customer {
protected:
	string customerName;
	int patienceLevel;
	int budget;
	int rowdiness;
	int minRep;

	string* pref = nullptr;
	int prefSize;
	bool onlyPref; //Limit order to preferences only 
	
	//Dialouge
	string Denter;
	string Ddeclined;
	string DstartOrder;
	string DsubmitOrder;
	string DOrderGood;
	string DOrderBad;
	string DWaitToLong;
	string DrepTooLow;

public:
	virtual ~Customer(){}

	string getPref();
	string getPrefAt(int);
	int getPrefSize();
	bool getOnlyPref();

	string getName();
	int getPatience();
	int getBudget();
	int getRowdiness();
	int getMinRep();

	string getDEnter();
	string getDdeclined();
	string getDstartOrder();
	string getDsubmitOrder();
	string getDOrderGood();
	string getDOrderBad();
	string getDWaitToLong();
	string getDrepTooLow();
};