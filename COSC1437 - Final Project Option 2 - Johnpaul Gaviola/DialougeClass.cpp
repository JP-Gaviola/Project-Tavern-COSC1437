#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "DialougeClass.h"
#include <thread> // standard C++11


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

void Dialouge::writeDialouge(string dia, bool keyContinue)
{
    for (int i = 0; i < dia.size(); i++)
    {
        cout << dia.at(i) << flush;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
	cout << endl;
	if (keyContinue) { system("pause"); }
}

void Dialouge::askUserChoice(string& choiceVar)
{
    cout << "Enter Choice:";
    cin >> choiceVar;
}