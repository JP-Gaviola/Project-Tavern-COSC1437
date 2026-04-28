#include "GameStats.h"
using namespace std;

GameStats::GameStats()
{
	Day = 0;
	Quota = 100;
	Earnings = 0;
	//Time is managed in another class
	HappyHour = false;
}

GameStats::GameStats(int inD, int inQ, int inE, bool inH)
{
	Day = inD;
	Quota = inQ; //Calculated on game start from this point
	Earnings = inE;
	HappyHour = inH;
}

void GameStats::setDay(int in) { Day = in; }
void GameStats::setQuota(int in) { Quota = in; }
void GameStats::setEarnings(int in) { Earnings = in; }
void GameStats::changeHappyHour(bool in) { HappyHour = in; }
void GameStats::addEarnings(int in) { Earnings += in; }

int GameStats::getDay() { return Day; }
int GameStats::getQuota() { return Quota; }
int GameStats::getEarnings() { return Earnings; }
bool GameStats::checkHappyHour() { return HappyHour; }

