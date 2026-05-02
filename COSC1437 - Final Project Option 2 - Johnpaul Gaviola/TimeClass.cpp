#include "TimeClass.h"
#include <string>
#include <chrono>   // For duration
#include <thread>   // For sleep_for

using namespace std;

TimeClass::TimeClass()
{
	Hour = 9;
	Min = 0;
	timeActive = false;
	reachedEnd = false;
	restartTime = false;
}

void TimeClass::startTime()
{
	//Run in a seperate thread
	//Reset
	timeActive = true;
	while (timeActive)
	{
		if (Hour >= 21)
		{
			reachedEnd = true;
			break;
		}

		if ((Min += 1) >= 60)
		{
			Hour += 1;
			Min = 0;
		}
		else
		{
			Min += 1;
		}
		this_thread::sleep_for(chrono::milliseconds(500)); //500 mili = 6 minutes per day 

		if (restartTime)
		{
			Hour = 9;
			Min = 0;
			timeActive = true;
			reachedEnd = false;
			restartTime = false;
		}
	}
}
