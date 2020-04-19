#pragma once
#include"State.h"
#include"D3D.h"
class NumberInput : public State
{
private:
	bool checkInput(int unicode);
public:
	NumberInput(MyD3D& d3d, std::string& baseString, std::string& string) :
		State(d3d, baseString, string)
	{}
	void update();
	int getNextScene();
};

