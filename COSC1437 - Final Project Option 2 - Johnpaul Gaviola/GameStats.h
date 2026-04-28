#pragma once

using namespace std;

class GameStats {
public:
	GameStats();
	GameStats(int, int, int, bool);

	void setDay(int);
	void setQuota(int);
	void setEarnings(int);
	void addEarnings(int);
	void changeHappyHour(bool);

	int getDay();
	int getQuota();
	int getEarnings();
	bool checkHappyHour();

private:
	int Day;
	int Quota;
	int Earnings;
	//Time is managed in another class
	bool HappyHour;

};