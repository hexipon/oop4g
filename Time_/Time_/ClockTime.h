#pragma once
class ClockTime
{
private:
	float timeInSeconds;
public:
	void updateTime(const float);
	void setTime(const int);
	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;
};

