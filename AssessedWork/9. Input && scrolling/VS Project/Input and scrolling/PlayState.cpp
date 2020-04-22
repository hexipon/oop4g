#include "PlayState.h"
#include"Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayState::PlayState(d3d & _d3d)
	:_d3d(_d3d), Player(_d3d)
{
	InitBgnd();
	InitPlayer();
}

void PlayState::Update(float dTime)
{
	//scroll background layers
	int i = 1;
	for (auto& s : Bgnd)
		s.Scroll(dTime*(i++)*SCROLL_SPEED, 0);

	Vector2 mouse{ Game::mouseAndKeyInput.GetMousePos(false) };

	if (Game::mouseAndKeyInput.IsPressed(VK_UP) ||
		Game::mouseAndKeyInput.IsPressed(VK_DOWN) ||
		Game::mouseAndKeyInput.IsPressed(VK_RIGHT) ||
		Game::mouseAndKeyInput.IsPressed(VK_LEFT) ||
		(mouse.Length() > 0.0001f) ||
		Game::GamepadInput.IsConnected(0))
	{
		//move the ship
		Vector2 pos{ Player.GetPosition() };
		if (Game::mouseAndKeyInput.IsPressed(VK_UP))
			pos.y -= SPEED * dTime;
		else if (Game::mouseAndKeyInput.IsPressed(VK_DOWN))
			pos.y += SPEED * dTime;
		if (Game::mouseAndKeyInput.IsPressed(VK_RIGHT))
			pos.x += SPEED * dTime;
		else if (Game::mouseAndKeyInput.IsPressed(VK_LEFT))
			pos.x -= SPEED * dTime;

			pos += mouse * MOUSE_SPEED * dTime;

		if (Game::GamepadInput.IsConnected(0))
		{
			DBOUT("left stick x=" << Game::GamepadInput.GetState(0).leftStickX << " y=" << Game::GamepadInput.GetState(0).leftStickY);
			pos.x += Game::GamepadInput.GetState(0).leftStickX * PAD_SPEED * dTime;
			pos.y -= Game::GamepadInput.GetState(0).leftStickY * PAD_SPEED * dTime;
		}

		//keep it within window
		if (pos.x < PlayArea.left)
			pos.x = PlayArea.left;
		else if (pos.x > PlayArea.right)
			pos.x = PlayArea.right;
		if (pos.y < PlayArea.top)
			pos.y = PlayArea.top;
		else if (pos.y > PlayArea.bottom)
			pos.y = PlayArea.bottom;
		Player.SetPosition(pos);
	}
}

void PlayState::Render1(float dTime, DirectX::SpriteBatch& batch)
{
	Sprite spr(_d3d);
	spr.SetTex(*_d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "2dsprite.dds", "", true));
	spr.SetScale(Vector2(0.25f, 0.25f));
	spr.Draw(batch);

	RECTF dim{ 0,0,1024,1024 };
	spr.SetTexRect(dim);
	spr.SetPosition(Vector2(100, 100));
	spr.SetScale(Vector2(0.125f, 0.125f));
	spr.Draw(batch);



}


void PlayState::Render(float dTime, DirectX::SpriteBatch & batch) 
{
	for (auto& s : Bgnd)
		s.Draw(batch);
	Player.Draw(batch);
}

void PlayState::InitBgnd()
{
	Bgnd.insert(Bgnd.begin(), BGND_LAYERS, Sprite(_d3d));

	pair<string, string> files[BGND_LAYERS]{
		{ "bgnd0","backgrounds/starfield_noalpha.dds" },
		{ "bgnd1","backgrounds/starfield2_alpha.dds" },
		{ "bgnd2","backgrounds/starfield3_alpha.dds" }
	};
	int i = 0;
	for (auto& f : files)
	{
		ID3D11ShaderResourceView *p = _d3d.GetCache().LoadTexture(&_d3d.GetDevice(), f.second, f.first);
		if (!p)
			assert(false);
		Bgnd[i++].SetTex(*p);
	}

}


void PlayState::InitPlayer()
{
	//load the ship
	ID3D11ShaderResourceView *p = _d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "ship.dds");
	Player.SetTex(*p);
	Player.SetScale(Vector2(0.1f, 0.1f));
	Player.SetOrigin(Player.GetTexData().dim / 2.f);
	Player.SetRotation(90 * 0.01745329252);
	//setup play area
	int w, h;
	WinUtil::Get().GetClientExtents(w, h);
	PlayArea.left = Player.GetScreenSize().x*0.5f;
	PlayArea.top = Player.GetScreenSize().y * 0.5f;
	PlayArea.right = w - PlayArea.left;
	PlayArea.bottom = h - Player.GetScreenSize().y * 0.5f;
	Player.SetPosition(Vector2(PlayArea.left + Player.GetScreenSize().x / 2.f, (PlayArea.bottom - PlayArea.top) / 2.f));
}
