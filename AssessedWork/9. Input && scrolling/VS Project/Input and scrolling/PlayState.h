#pragma once
#include <vector>


#include "Sprite.h"

class Game;
class PlayState
{
public:
	PlayState(d3d& d3d);
	void Update(float dTime);
	void Render(float dTime, DirectX::SpriteBatch& batch);
private:
	const float SCROLL_SPEED = 5.f;
	static const int BGND_LAYERS = 3;
	const float SPEED = 250;
	const float MOUSE_SPEED = 5000;
	const float PAD_SPEED = 5000;
	d3d& _d3d;
	std::vector<Sprite> Bgnd;
	Sprite Player;
	RECTF PlayArea;

	void InitBgnd();
	void InitPlayer();
	void Render1(float dTime, DirectX::SpriteBatch& batch);
};