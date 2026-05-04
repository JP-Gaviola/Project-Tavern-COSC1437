#pragma once

//9:00 -> 21:00
//Happy hour at 17:00
#include <string>
#include "GameStats.h"
using namespace std;

class TimeClass {
public:
	TimeClass();

	void startTime(GameStats*);

	int Hour;
	int Min;
	bool timeActive;
	bool reachedEnd;
	bool restartTime;
};