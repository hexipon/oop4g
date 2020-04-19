#include "AnClock.h"

AnClock::AnClock(const int i, const DirectX::SimpleMath::Vector2 pos, MyD3D& d3d) : position(pos)
{


	font = new DirectX::SpriteFont(&d3d.GetDevice(), L"../bin/data/Retro.spritefont");

	clockNum = std::to_string(i);

	//baseImg.setTexture(tex);
	//baseImg.setPosition(sf::Vector2f(position.x + baseImg.getGlobalBounds().width / 2, position.y + baseImg.getGlobalBounds().height / 2));
	//baseImg.setScale(0.5, 0.5);
	//clockNum.setFont(font);
	//clockNum.setPosition(baseImg.getPosition());
	//clockNum.setLetterSpacing(1);
	//clockNum.setScale(1, 1);
}

void AnClock::setNewTime(const Time & time)
{
	AnTime = time;
}
void AnClock::setNewTime()
{
	AnTime.setRandTime();
}

Time AnClock::getTime()
{
	return AnTime;
}

void AnClock::update(float& deltaTime)
{
	float hour = AnTime.getHours();
	if (hour >= 12)
		hour = hour - 12;
	hour = hour + (AnTime.getMinutes() / 60.f);

	AnTime.update(deltaTime);
	bigHandRotation = ((float)(AnTime.getMinutes() * 6));
	smallHandRotation = ((float)(hour*30.f));
}

void AnClock::render(MyD3D& d3d, DirectX::SpriteBatch* spritebatch)
{
	//convert string to characters
	char * writable = new char[clockNum.size() + 1];
	std::copy(clockNum.begin(), clockNum.end(), writable);
	writable[clockNum.size()] = '\0'; // don't forget the terminating 0

	Sprite spr(d3d);
	spr.SetTex(*d3d.GetCache().Get("clock_face").pTex);
	spr.SetPos(position);
	spr.SetScale({ 0.5f,0.5f });
	spr.Draw(*spritebatch);
	spr.SetTex(*d3d.GetCache().Get("clock_hands").pTex);
	spr.SetScale({ 0.25f,0.25f });
	spr.SetOrigin({ 33, 455 });
	spr.SetTexRect({ 91,0,153,480 });
	spr.SetPos(DirectX::SimpleMath::Vector2(position.x + 129, position.y + 129));
	spr.setRotation(0.01745329252*bigHandRotation);
	spr.Draw(*spritebatch);
	spr.SetOrigin({ 49, 454.5f });
	spr.SetTexRect({ 0,0,91,480 });
	spr.SetPos(DirectX::SimpleMath::Vector2(position.x + 129, position.y + 129));
	spr.setRotation(0.01745329252*smallHandRotation);
	spr.Draw(*spritebatch);


	font->DrawString(spritebatch, writable, position);
}
