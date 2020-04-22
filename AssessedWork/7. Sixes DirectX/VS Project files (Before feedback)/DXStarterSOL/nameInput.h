#pragma once
#include"State.h"
class NameInput : public State
{
private:
	bool checkInput(int unicode);
public:
	NameInput(MyD3D& d3d, std::string& baseString, std::string& string) :
		State(d3d, baseString, string)
	{}
	void update();
	int getNextScene();
};

