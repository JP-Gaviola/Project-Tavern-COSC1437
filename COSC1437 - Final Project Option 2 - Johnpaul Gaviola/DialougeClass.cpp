#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "DialougeClass.h"

Dialouge::~Dialouge()
{
    delete[] diaData;
}

bool Dialouge::loadDialouge(string filename)
{
    int counter = 0;
    //load all dialogue files
    ifstream rEADER;
   

    //First read line amount 
    rEADER.open(filename);
    if (rEADER.is_open() && rEADER.good())
    {
        string tempstring;
        while (getline(rEADER, tempstring))
        {
            counter++;
        }
    }
    else{return false;}
    
    rEADER.close();

    //reopen to load into array 
    string* newArray = new string[counter];
    counter = 0;

    //reopen and load data
    rEADER.open(filename);

    if (rEADER.is_open() && rEADER.good())
    {
        while (getline(rEADER, newArray[counter]))
        {
            counter++;
        }
    }
    else { cout << "2nd check failed" << endl; return false; }

    //delete[] diaData;
    *diaData = newArray;
    return true;
}

void Dialouge::printLogo()
{
    cout << R"( __    __                                                __                                     
|  \  |  \                                              |  \                                    
| $$  | $$  ______    ______    ______   __    __       | $$____    ______   __    __   ______  
| $$__| $$ |      \  /      \  /      \ |  \  |  \      | $$    \  /      \ |  \  |  \ /      \ 
| $$    $$  \$$$$$$\|  $$$$$$\|  $$$$$$\| $$  | $$      | $$$$$$$\|  $$$$$$\| $$  | $$|  $$$$$$\
| $$$$$$$$ /      $$| $$  | $$| $$  | $$| $$  | $$      | $$  | $$| $$  | $$| $$  | $$| $$   \$$
| $$  | $$|  $$$$$$$| $$__/ $$| $$__/ $$| $$__/ $$      | $$  | $$| $$__/ $$| $$__/ $$| $$      
| $$  | $$ \$$    $$| $$    $$| $$    $$ \$$    $$      | $$  | $$ \$$    $$ \$$    $$| $$      
 \$$   \$$  \$$$$$$$| $$$$$$$ | $$$$$$$  _\$$$$$$$       \$$   \$$  \$$$$$$   \$$$$$$  \$$      
                    | $$      | $$      |  \__| $$                                              
                    | $$      | $$       \$$    $$                                              
                     \$$       \$$        \$$$$$$                                               )" << endl;
}

void Dialouge::writeDialouge(int diaLine, bool keyContinue)
{
	cout << diaData[diaLine] << endl;
	if (keyContinue) { system("pause"); }
}