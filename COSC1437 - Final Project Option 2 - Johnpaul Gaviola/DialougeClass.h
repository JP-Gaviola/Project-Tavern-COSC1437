#pragma once
#include <string>
#include <iostream>
using namespace std;

class Dialouge
{
	public:
		void writeDialouge(string dia, bool keyContinue, bool oneAtATime); //Writes dialouge 
		void printLogo(); //Prints logo of the game
		void askUserChoice(string& choiceVar);
};