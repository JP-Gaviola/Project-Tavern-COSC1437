#pragma once

//9:00 -> 21:00
//Happy hour at 17:00
#include <string>
#include <chrono>   // For duration
#include <thread>   // For sleep_for


using namespace std;

class CustomerTimer {
public:

	void startTime()
	{
		
		timeActive = true;
		while (timeActive)
		{
			elapsed++;
			this_thread::sleep_for(chrono::seconds(1));
		}
	}

	int elapsed = 0;
	bool timeActive = false;
};