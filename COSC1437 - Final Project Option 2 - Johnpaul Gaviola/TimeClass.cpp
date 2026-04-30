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
}

void TimeClass::startTime()
{
	//Run in a seperate thread
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
		this_thread::sleep_for(chrono::seconds(1));
	}
}