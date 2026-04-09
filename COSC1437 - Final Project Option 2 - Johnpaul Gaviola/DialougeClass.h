#pragma once
#include <string>
#include <iostream>
using namespace std;

class Dialouge
{
	public:
		void writeDialouge(string inpText, bool keyContinue); //Writes dialouge 
};

void Dialouge::writeDialouge(string inpText, bool keyContinue)
{
	cout << inpText << endl;
	if (keyContinue) { system("pause"); }
}