#include "ClockTime.h"


void ClockTime::updateTime(const float dt)
{
	timeInSeconds += dt;
	if (timeInSeconds >= 86400)
		timeInSeconds = 0;
}

void ClockTime::setTime(const int time)
{
	timeInSeconds = static_cast<float>(time);
}

int ClockTime::getHours() const
{
	return (static_cast<int>(timeInSeconds) / 3600);
}

int ClockTime::getMinutes() const
{
	return ((static_cast<int>(timeInSeconds) % 3600) / 60);
}

int ClockTime::getSeconds() const
{
	return ((static_cast<int>(timeInSeconds) % 3600) % 60);
}