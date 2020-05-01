#include "Animation.h"
#include"Sprite.h"

void Animation::Init(int _start, int _stop, float _rate, bool _loop)
{
	ElapsedSec = 0;
	Start = _start;
	Stop = _stop;
	RateSec = _rate;
	Loop = _loop;
	_Sprite.SetFrame(Start);
	Current = Start;
}

void Animation::Update(float _elapsedSec)
{
	if (!_Play)
		return;
	ElapsedSec += _elapsedSec;
	if (ElapsedSec > (1.f / RateSec))
	{
		ElapsedSec = 0;
		Current++;
		if (Current > Stop)
		{
			if (Loop)
				Current = Start;
			else
				Current = Stop;
		}
		_Sprite.SetFrame(Current);
	}
}

Animation& Animation::operator=(const Animation& rhs)
{
	Start = rhs.Start;
	Stop = rhs.Stop;
	Current = rhs.Current;
	RateSec = rhs.RateSec;
	ElapsedSec = rhs.ElapsedSec;
	Loop = rhs.Loop;
	_Play = rhs._Play;
	return *this;
}