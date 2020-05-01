#pragma once
#include<string>
#include"D3D.h"
class State
{
protected:
	MyD3D& d3d;
	std::string& baseString;
	std::string& string;
	virtual bool checkInput(int code) = 0;
	State(MyD3D& d3d, std::string& baseString, std::string& string) :
		d3d(d3d),
		baseString(baseString),
		string(string)
	{}
public:
	virtual void update() = 0;
	void updateInput(char wParam);
	void backspace();
	virtual int getNextScene() = 0;
};

