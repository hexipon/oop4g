#pragma once
class Sprite;
class Animation {
private:
	int Start = 0, Stop = 0, Current = 0;
	float RateSec = 0;		
	float ElapsedSec = 0;	
	bool Loop = false;		
	bool _Play = false;		
	Sprite& _Sprite;		

public:
	Animation(Sprite& spr)
		:_Sprite(spr)
	{}
	void Init(int _start, int _stop, float _rate, bool _loop);
	void Update(float _elapsedSec);
	void Play(bool go) {
		_Play = go;
	}
	void SetFrame(int idx) {
		Current = idx;
	}
	int GetStart() const { return Start; }
	int GetEnd() const { return Stop; }
	Animation& operator=(const Animation& rhs);
};