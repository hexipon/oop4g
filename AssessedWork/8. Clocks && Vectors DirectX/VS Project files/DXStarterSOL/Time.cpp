#include "Time.h"
#include "Time.h"
Time::Time() {	//default constructor
	setRandTime();
}

Time::Time(const Time& t)
	: hrs_(t.hrs_), mins_(t.mins_), secs_(t.secs_)
{

}

Time::Time(int h, int m, int s)
	: hrs_(h), mins_(m), secs_(s)
{

}

Time::Time(long long s)
	: hrs_(((s / 60) / 60) % 24),
	mins_((s / 60) % 60),
	secs_(s % 60)
{

}
Time::Time(const std::string& s) { 	
	std::istringstream is_time(s);
	char ch;
	is_time >> hrs_ >> ch >> mins_ >> ch >> secs_;

}

Time::~Time() {

}
int Time::getHours() const {
	return hrs_;
}
int Time::getMinutes() const {
	return mins_;
}
int Time::getSeconds() const {
	return secs_;
}
void Time::setTime(int h, int m, int s) {
	hrs_ = h;
	mins_ = m;
	secs_ = s;
}
void Time::setRandTime()
{
	//std::mt19937 rng(std::time(NULL));

	//std::uniform_int_distribution<int> range(0, 86400);


	const long long s = rand() % 86400 + 1;
	hrs_ = (((s / 60) / 60) % 24);
	mins_ = ((s / 60) % 60);
	secs_ = 0; //set seconds to zero so the clocks tick at the same time
}
long long Time::toSeconds() const {
	return ((hrs_ * 3600) + (mins_ * 60) + secs_);
}
void Time::update(const float& deltaTime)
{
	tick += deltaTime;
	if (tick >= 1)
	{
		secs_ += 1;
		if (secs_ >= 60)
		{
			secs_ = 0;
			mins_ += 1;
			if (mins_ >= 60)
			{
				mins_ = 0;
				hrs_ += 1;
				if (hrs_ >= 24)
					hrs_ = 0;
			}
		}
		tick = 0;
	}
}