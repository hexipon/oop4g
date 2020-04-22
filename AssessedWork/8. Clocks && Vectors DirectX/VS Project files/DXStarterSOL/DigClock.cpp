#include "DigClock.h"
void DigClock::init(MyD3D& d3d)
{


	font = new DirectX::SpriteFont(&d3d.GetDevice(), L"../bin/data/digital-7.spritefont");

	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "digital_clock.dds");

}

void DigClock::update(float& deltaTime)
{
	//conv time to string
	DiTime.update(deltaTime);
	std::ostringstream os;
	const char prev(os.fill('0'));
	os << std::setw(2) << std::to_string(DiTime.getHours()) << ':'
		<< std::setw(2) << std::to_string(DiTime.getMinutes()) << ':'
		<< std::setw(2) << std::to_string(DiTime.getSeconds());
	os.fill(prev);
	timeT = (os.str());
}

void DigClock::render(MyD3D& d3d, DirectX::SpriteBatch* spritebatch)
{
	//convert string to characters
	char * writable = new char[timeT.size() + 1];
	std::copy(timeT.begin(), timeT.end(), writable);
	writable[timeT.size()] = '\0'; // don't forget the terminating 0
	
	Sprite spr(d3d);
	spr.SetTex(*d3d.GetCache().Get("digital_clock").Tex);
	spr.SetPos(position);
	spr.SetScale({ 0.3f,0.3f });
	spr.Draw(*spritebatch);
	font->DrawString(spritebatch, writable, DirectX::SimpleMath::Vector2(position.x + 15, position.y + 35), Colours::White, 0.f, {0,0}, 1.8f);
}
