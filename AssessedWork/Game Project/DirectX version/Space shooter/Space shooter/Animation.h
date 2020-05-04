#pragma once
class Sprite;
class Animation {
private:
	int Start=0, Stop=0, Current=0;
	float RateSec=0;
	float ElapsedSec=0;
	bool Loop=false;
	bool _Play=false;
	Sprite& _Sprite;		

public:
	Animation(Sprite& spr)
		:_Sprite(spr)
	{}
	void Init(const int _start, const int _stop, const float _rate, const bool _loop);
	void Update(const float _elapsedSec);
	void Play(const bool go) {
		_Play = go;
	}
	void SetFrame(const int idx) {
		Current = idx;
	}
	int GetStart() const { return Start; }
	int GetEnd() const { return Stop; }
	Animation& operator=(const Animation& rhs);
};