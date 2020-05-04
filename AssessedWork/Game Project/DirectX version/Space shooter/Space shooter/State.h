#pragma once
#include"d3d.h"
#include"SpriteBatch.h"
class State
{
protected:
	d3d& _d3d;
	DirectX::SpriteBatch& _spriteBatch;
	float& _deltaTime;
	State(d3d& d3d_, DirectX::SpriteBatch& spriteBatch_, float& deltaTime_) : _d3d(d3d_), _spriteBatch(spriteBatch_), _deltaTime(deltaTime_) {}
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void sizeSetup() =0;
};

