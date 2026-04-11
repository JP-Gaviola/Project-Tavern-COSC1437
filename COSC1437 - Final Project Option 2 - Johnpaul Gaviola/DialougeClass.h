#pragma once
#include <string>
#include <iostream>
using namespace std;

class Dialouge
{
	public:
		~Dialouge(); //frees memory from dia table

		bool loadDialouge(string); //loads a dialouge data to this object's dia
		void writeDialouge(int diaLine, bool keyContinue); //Writes dialouge 
		void printLogo(); //Prints logo of the game

	private:
		string* diaData[];
		
};