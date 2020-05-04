#include "playState.h"
#include"GameManager.h"
#include"Animation.h"

const RECTF thrustAnim[]{
	{ 0,  0, 15, 16},
	{ 16, 0, 31, 16 },
	{ 32, 0, 47, 16 },
	{ 48, 0, 64, 16 },
};

void playState::update(const float & deltaTime, d3d& _d3d)
{
	updateBackground(deltaTime);
	updateAsteroids(deltaTime);
	updateMissiles(deltaTime, _d3d);
	updatePlayer(deltaTime);
	UpdateThrust(deltaTime);
}

void playState::render(d3d & _d3d, DirectX::SpriteBatch & spritebatch)
{
	for (auto& s : Bgnd)
		s.Draw(spritebatch);

	Player.Draw(spritebatch);

 	if (Thrusting > GetClock())
		Thrust.Draw(spritebatch);

	for (auto& asteroid : Asteroids)
		if(asteroid.active)
			asteroid.Render(spritebatch);

	for (auto& missile : Missiles)
		if(missile.active)
			missile.Render(spritebatch);

	_score.Render(spritebatch);
}

void playState::InitBackground(d3d& _d3d)
{
	Bgnd.insert(Bgnd.begin(), BGND_LAYERS, Sprite(_d3d));

	Bgnd[0].SetTex(*_d3d.GetCache().Get("noalpha").pTex);
	Bgnd[1].SetTex(*_d3d.GetCache().Get("star1alpha").pTex);
	Bgnd[2].SetTex(*_d3d.GetCache().Get("star2alpha").pTex);
}

void playState::InitPlayer(d3d& _d3d)
{
	Player.Init(_d3d);
	//setup play area
	int w, h;
	WindowUtils::Get().GetClientExtents(w, h);
	PlayArea.left = 0;
	PlayArea.top = 0;
	PlayArea.right = w - PlayArea.left;
	PlayArea.bottom = h - Player.GetScreenSize().y;

	//setup thrust animation
	std::vector<RECTF> frames(thrustAnim, thrustAnim + sizeof(thrustAnim) / sizeof(thrustAnim[0]));
	ID3D11ShaderResourceView *p = _d3d.GetCache().LoadTexture(&_d3d.GetDevice(), "thrust.dds", "thrust", true, &frames);
	Thrust.SetTex(*p);
	Thrust.GetAnim().Init(0, 3, 15, true);
	Thrust.GetAnim().Play(true);
	Thrust.SetRotation(90.f * 0.01745329252f);
	//set player position
	Player.SetPosition(DirectX::SimpleMath::Vector2(PlayArea.left + (Thrust.GetScreenSize().x*2), (h / 2) - (Player.GetScreenSize().y / 2.f)));


}
void playState::UpdateThrust(float dTime)
{
	if (Thrusting)
	{
		Thrust.SetPosition({ Player.GetPosition().x, Player.GetPosition().y + Player.GetScreenSize().y/2  - Thrust.GetScreenSize().y/2});
		Thrust.SetScale(DirectX::SimpleMath::Vector2(2.f, 2.f));
		Thrust.GetAnim().Update(dTime);
	}
}
const void playState::updateBackground(const float& deltaTime)
{
	//scroll background layers
	int i = 1;
	for (auto& s : Bgnd)
		s.Scroll((deltaTime*(i++)) * 20, 0);
	return void();
}
const void playState::updateAsteroids(const float& deltaTime)
{
	for (auto& a : Asteroids)
	{
		if (a.active)
		{
			a.Update(deltaTime);
			if (a.CheckCollision(Player.GetSprite()))
				GameManager::Get().changeState(GameManager::gameStates::Lost);
			for (auto& _Missile : Missiles)
				if (_Missile.active)
				{
					if (_Missile.CheckCollision(a.spr))
					{
						a.health -= 1;
						_Missile.active = false;
					}
				}
		}

	}
	if ((GetClock() - LastSpawn) > SpawnRateSec)
	{
		if (SpawnAsteroid())
			LastSpawn = GetClock();
	}
	return void();
}
const void playState::updateMissiles(const float & deltaTime, d3d& _d3d)
{
	if ((GameManager::mouseAndKeyInput.IsPressed(VK_SPACE) || GameManager::GamepadInput.IsPressed(0, XINPUT_GAMEPAD_B)) && GetClock() > missileTimer)
	{
		Missiles.push_back(Missile(_d3d));
		Missiles.back().Init(_d3d);
		Missiles.back().spr.GetAnim().Play(true);
		Missiles.back().spr.SetPosition(DirectX::SimpleMath::Vector2(Player.GetPosition().x + Player.GetScreenSize().x,
			Player.GetPosition().y + (Player.GetScreenSize().y / 2) - (Missiles.back().spr.GetScreenSize().y / 2)));
		Missiles.back().active = true;
		missileTimer = GetClock() + gameConstants::missile_debounce;
	}
	for (unsigned int i = 0; i < Missiles.size(); i++)
	{
		if (Missiles[i].active)
			Missiles[i].Update(deltaTime);
		if (Missiles[i].spr.GetPosition().x > gameConstants::WindowSize.x)
		{
			Missiles[i].active = false;
			//bad work around as trying to erase an element from the vector keeps giving me xutility errors
		}
	}

	return void();
}
const void playState::updatePlayer(const float & deltaTime)
{
	const bool keyboardInput = GameManager::mouseAndKeyInput.IsPressed(VK_UP) || GameManager::mouseAndKeyInput.IsPressed(VK_DOWN) ||
		GameManager::mouseAndKeyInput.IsPressed(VK_W) || GameManager::mouseAndKeyInput.IsPressed(VK_S);

	const bool gamepadInput = (GameManager::GamepadInput.IsConnected(0) && GameManager::GamepadInput.GetState(0).leftStickY != 0);

	if (keyboardInput || gamepadInput)
	{
		Player.Update(deltaTime, PlayArea);
		Thrusting = GetClock() + 0.1f;
	}
	return void();
}
Asteroid* playState::SpawnAsteroid()
{
	size_t i = 0;
	Asteroid*p = nullptr;
	while (i < Asteroids.size() && !p)
	{
		if (!Asteroids[i].active)
			p = &Asteroids[i];
		++i;
	}

	if (p)
	{
		int w, h;
		WindowUtils::Get().GetClientExtents(w, h);
		float radius = Asteroids[0].spr.GetScreenSize().Length() / 2.f;
		DirectX::SimpleMath::Vector2& pos = p->spr.GetPosition();
		pos.x = (float)(w + radius);
		pos.y = (float)(rand() % h + 1);
		p->spr.SetPosition(DirectX::SimpleMath::Vector2(pos.x - 20 - (p->spr.GetScreenSize().x / 2.f), pos.y - (p->spr.GetScreenSize().y / 2.f)));
			p->active = true;
	}
	return p;
}

void playState::InitAsteroids(d3d& _d3d)
{
	Asteroids.clear();
	Asteroid asteroid(_d3d);
	asteroid.Init(_d3d);
	Asteroids.insert(Asteroids.begin(), 10, asteroid);
	for (auto& a : Asteroids)
	{
		if ((rand() % 2 - 1) == 0)
			a.spr.GetAnim().Init(0, 31, (float)(rand() % 20 + 10), true);
		else
			a.spr.GetAnim().Init(32, 63, (float)(rand() % 20 + 10), true);
		a.spr.GetAnim().SetFrame((rand() % a.spr.GetAnim().GetEnd() + a.spr.GetAnim().GetStart()));
		a.spr.GetAnim().Play(true);
	}
}
