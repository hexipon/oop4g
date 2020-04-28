#pragma once
#include <ctime>
#include <string>	
#include <iostream>	
#include <sstream>	
#include <iomanip>	
class Time {
public:
	Time();
	Time(const Time&);

	Time(int h, int m, int s);
	Time(long long);
	Time(const std::string& timeAsString);

	~Time();
	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;
	void setTime(int, int, int);
	void setRandTime();
	void update(const float& deltaTime);
private:
	float tick = 0.f;
	int hrs_, mins_, secs_;
	long long toSeconds() const;
};