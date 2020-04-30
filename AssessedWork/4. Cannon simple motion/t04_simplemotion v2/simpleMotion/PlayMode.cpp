#include "PlayMode.h"
#include"Game.h"
//******************************************************************
//a mini playable game (sort of)
void PlayMode::Init()
{
	if (!CannonTex.loadFromFile("../data/cannon.png"))
		assert(false);
	CannonTex.setSmooth(false);
	
	mpGun->SetTexture(CannonTex, sf::IntRect(0, 0, 156, 138));
	mpGun->SetOrigin(Vec2f{ 69, 73 });
	mpGun->SetPos(Vec2f{ GDC::SCREEN_RES.x / 2.f, GDC::SCREEN_RES.y / 2.f });

	ball.SetTexture(CannonTex, sf::IntRect(4, 147, 38, 38));
	ball.SetOrigin(Vec2f{ 19, 19 });
	ball.SetPos(mpGun->GetPos());


	if (!WallTex.loadFromFile("../data/tiledwall.png"))
		assert(false);
	WallTex.setRepeated(true);
	WallTex.setSmooth(true);

	//resolution independant with the sprite scaled up/down as necessary
	//the texture is set to wrap and uses a 'tilable' brick pattern so it can grow to any size
	Walls[Wall::TOP].SetTexture(WallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*(1 - GDC::WALL_WDITH * 2)), (int)(GDC::SCREEN_RES.y*GDC::WALL_WDITH) });
	Walls[Wall::TOP].SetPos(Vec2f{ GDC::SCREEN_RES.x*GDC::WALL_WDITH,0 });
	Walls[Wall::TOP].SetOrigin(Vec2f{ 0,0 });
	Walls[Wall::TOP].Init(Wall::TOP);

	Walls[Wall::BOTTOM].SetTexture(WallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*(1 - GDC::WALL_WDITH * 2)), (int)(GDC::SCREEN_RES.y*GDC::WALL_WDITH) });
	Walls[Wall::BOTTOM].SetPos(Vec2f{ GDC::SCREEN_RES.x*GDC::WALL_WDITH,GDC::SCREEN_RES.y*(1 - GDC::WALL_WDITH) });
	Walls[Wall::BOTTOM].SetOrigin(Vec2f{ 0,0 });
	Walls[Wall::BOTTOM].Init(Wall::BOTTOM);

	Walls[Wall::LEFT].SetTexture(WallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*GDC::WALL_WDITH), (int)(GDC::SCREEN_RES.y*(1 - GDC::WALL_WDITH * 2)) });
	Walls[Wall::LEFT].SetPos(Vec2f{ 0,GDC::SCREEN_RES.y*GDC::WALL_WDITH });
	Walls[Wall::LEFT].SetOrigin(Vec2f{ 0,0 });
	Walls[Wall::LEFT].Init(Wall::LEFT);

	Walls[Wall::RIGHT].SetOrigin(Vec2f{ 0,0 });
	Walls[Wall::RIGHT].SetPos(Vec2f{ GDC::SCREEN_RES.x*(1 - GDC::WALL_WDITH),GDC::SCREEN_RES.y*GDC::WALL_WDITH });
	Walls[Wall::RIGHT].SetTexture(WallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*GDC::WALL_WDITH), (int)(GDC::SCREEN_RES.y*(1 - GDC::WALL_WDITH * 2)) });
	Walls[Wall::RIGHT].Init(Wall::RIGHT);

}

void PlayMode::Update()
{

	mpGun->Update();
	ball.Update();

	for (int i = 0; i < Wall::MAX_WALLS; ++i)
		Walls[i].Update();
}

void PlayMode::Render()
{
	//the instructions
	GD& gd = Game.GetData();
	std::string mssg = gd.playerName;
	mssg += ", press left or right arrow to spin, space to fire, ESC to quit";
	sf::Text txt(mssg, gd.font, textSize);
	txt.setPosition(GDC::SCREEN_RES.x*0.15f, GDC::SCREEN_RES.y*0.15f);
	gd.pWindow->draw(txt);

	ball.Render(*gd.pWindow); //make sure ball it under the cannon
	mpGun->Render(*gd.pWindow);
	for (int i = 0; i < Wall::MAX_WALLS; ++i)
		Walls[i].Render(*gd.pWindow);
}