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
	const float PAD_SPEED = 250;
	const float ConvertToRads{ 0.01745329252 };
	const float playerRotation{ 90 };
	const DirectX::SimpleMath::Vector2 playerScale{ 0.1,0.1 };
	d3d& _d3d;
	std::vector<Sprite> Bgnd;
	Sprite Player;
	RECTF PlayArea;

	void InitBgnd();
	void InitPlayer();
};