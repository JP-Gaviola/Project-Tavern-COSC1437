#include "Customer.h"
#include <string>
using namespace std;

//Maybe day requirement for some custoemrs

//getter
string Customer::getName() { return customerName; }
int Customer::getPatience() { return patienceLevel; }
int Customer::getBudget() { return budget; }
int Customer::getRowdiness() { return rowdiness; }
int Customer::getMinRep() { return minRep; }

//Pref
int Customer::getPrefSize() { return prefSize; }
string Customer::getPref() { return *pref; }
string Customer::getPrefAt(int i) { return pref[i]; }
bool Customer::getOnlyPref() { return onlyPref; }


//Dialoug
string Customer::getDEnter() { return Denter; }
string Customer::getDdeclined() { return Ddeclined; }
string Customer::getDstartOrder() { return DstartOrder; }
string Customer::getDsubmitOrder() { return DsubmitOrder; }
string Customer::getDOrderGood() { return DOrderGood; }
string Customer::getDOrderBad() { return DOrderBad; }
string Customer::getDWaitToLong() { return DWaitToLong; }
string Customer::getDrepTooLow() { return DrepTooLow; }