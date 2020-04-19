#pragma once
#include <vector>


#include "Sprite.h"

class Game;
//horizontal scrolling with player controlled ship
class PlayMode
{
public:
	PlayMode(d3d& d3d);
	void Update(float dTime);
	void Render(float dTime, DirectX::SpriteBatch& batch);
private:
	const float SCROLL_SPEED = 5.f;
	static const int BGND_LAYERS = 3;
	const float SPEED = 250;
	const float MOUSE_SPEED = 5000;
	const float PAD_SPEED = 500;
	d3d& mD3D;
	std::vector<Sprite> mBgnd; //parallax layers
	Sprite mPlayer;		//jet
	RECTF mPlayArea;	//don't go outside this	

	//setup once
	void InitBgnd();
	void InitPlayer();
	void Render1(float dTime, DirectX::SpriteBatch& batch);
};