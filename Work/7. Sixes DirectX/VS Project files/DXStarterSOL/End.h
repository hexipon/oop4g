#pragma once
#include"State.h"
class End : public State
{
private:
	bool checkInput(int unicode);
	const int& score;
public:
	End(MyD3D& d3d, std::string& baseString, std::string& string, const int& score) :
		State(d3d, baseString, string), score(score)
	{}
	void update();
	int getNextScene();
};

