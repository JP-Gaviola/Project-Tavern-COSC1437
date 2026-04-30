#pragma once
#include <chrono>   // For duration
#include <thread>   // For sleep_for

using namespace std;

class ElapsedTime {

public:
	int elap = 0;
	bool yesGo = true;

	void startCount()
	{
		while (yesGo)
		{
			elap++;
			this_thread::sleep_for(chrono::seconds(1));
		}
	}
};