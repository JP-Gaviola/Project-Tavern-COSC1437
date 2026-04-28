#pragma once
#include <string>
#include <iostream>
using namespace std;

class Dialouge
{
	public:
		void writeDialouge(string dia, bool keyContinue); //Writes dialouge 
		void printLogo(); //Prints logo of the game
		void askUserChoice(string& choiceVar);
};