#include "PlayMode.h"
#include"Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayMode::PlayMode(d3d & d3d)
	:mD3D(d3d), mPlayer(d3d)
{
	InitBgnd();
	InitPlayer();
}

void PlayMode::Update(float dTime)
{
	//scroll background layers
	int i = 1;
	for (auto& s : mBgnd)
		s.Scroll(dTime*(i++)*SCROLL_SPEED, 0);

	Vector2 mouse{ Game::sMKIn.GetMousePos(false) };

	if (Game::sMKIn.IsPressed(VK_UP) ||
		Game::sMKIn.IsPressed(VK_DOWN) ||
		Game::sMKIn.IsPressed(VK_RIGHT) ||
		Game::sMKIn.IsPressed(VK_LEFT) ||
		(mouse.Length() > VERY_SMALL) ||
		Game::sGamepads.IsConnected(0))
	{
		//move the ship
		Vector2 pos{ mPlayer.mPos };
		if (Game::sMKIn.IsPressed(VK_UP))
			pos.y -= SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_DOWN))
			pos.y += SPEED * dTime;
		if (Game::sMKIn.IsPressed(VK_RIGHT))
			pos.x += SPEED * dTime;
		else if (Game::sMKIn.IsPressed(VK_LEFT))
			pos.x -= SPEED * dTime;

			pos += mouse * MOUSE_SPEED * dTime;

		if (Game::sGamepads.IsConnected(0))
		{
			DBOUT("left stick x=" << Game::sGamepads.GetState(0).leftStickX << " y=" << Game::sGamepads.GetState(0).leftStickY);
			pos.x += Game::sGamepads.GetState(0).leftStickX * PAD_SPEED * dTime;
			pos.y -= Game::sGamepads.GetState(0).leftStickY * PAD_SPEED * dTime;
		}

		//keep it within the play area
		if (pos.x < mPlayArea.left)
			pos.x = mPlayArea.left;
		else if (pos.x > mPlayArea.right)
			pos.x = mPlayArea.right;
		if (pos.y < mPlayArea.top)
			pos.y = mPlayArea.top;
		else if (pos.y > mPlayArea.bottom)
			pos.y = mPlayArea.bottom;
		mPlayer.mPos = pos;
	}
}

void PlayMode::Render1(float dTime, DirectX::SpriteBatch& batch)
{
	Sprite spr(mD3D);
	spr.SetTex(*mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "2dsprite.dds", "", true));
	spr.SetScale(Vector2(0.25f, 0.25f));
	spr.Draw(batch);

	RECTF dim{ 0,0,1024,1024 };
	spr.SetTexRect(dim);
	spr.mPos = Vector2(100, 100);
	spr.SetScale(Vector2(0.125f, 0.125f));
	spr.Draw(batch);



}


void PlayMode::Render(float dTime, DirectX::SpriteBatch & batch) 
{
	for (auto& s : mBgnd)
		s.Draw(batch);
	mPlayer.Draw(batch);
}

void PlayMode::InitBgnd()
{
	//a sprite for each layer
	assert(mBgnd.empty());
	mBgnd.insert(mBgnd.begin(), BGND_LAYERS, Sprite(mD3D));

	//a neat way to package pairs of things (nicknames and filenames)
	pair<string, string> files[BGND_LAYERS]{
		{ "bgnd0","backgroundlayers/starfield_noalpha.dds" },
		{ "bgnd1","backgroundlayers/starfield2_alpha.dds" },
		{ "bgnd2","backgroundlayers/starfield3_alpha.dds" }
	};
	int i = 0;
	for (auto& f : files)
	{
		//set texture layers
		ID3D11ShaderResourceView *p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), f.second, f.first);
		if (!p)
			assert(false);
		mBgnd[i++].SetTex(*p);
	}

}


void PlayMode::InitPlayer()
{
	//load the ship
	ID3D11ShaderResourceView *p = mD3D.GetCache().LoadTexture(&mD3D.GetDevice(), "ship.dds");
	mPlayer.SetTex(*p);
	mPlayer.SetScale(Vector2(0.1f, 0.1f));
	mPlayer.origin = mPlayer.GetTexData().dim / 2.f;
	mPlayer.rotation = PI / 2.f;

	//setup play area
	int w, h;
	WinUtil::Get().GetClientExtents(w, h);
	mPlayArea.left = mPlayer.GetScreenSize().x*0.6f;
	mPlayArea.top = mPlayer.GetScreenSize().y * 0.6f;
	mPlayArea.right = w - mPlayArea.left;
	mPlayArea.bottom = h - mPlayer.GetScreenSize().y * 0.6f;
	mPlayer.mPos = Vector2(mPlayArea.left + mPlayer.GetScreenSize().x / 2.f, (mPlayArea.bottom - mPlayArea.top) / 2.f);
}
