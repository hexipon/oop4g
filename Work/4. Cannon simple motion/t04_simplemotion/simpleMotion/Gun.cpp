#include "Gun.h"
#include"Application.h"
void Gun::Update()
{
	if (mWaitSecs <= 0)
	{
		//here we don't want windowsOS keys, with initial delays and repeat rate delays and all that rubbish
		//so just access the keyboard directly for instant response
		float inc = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			inc = -GDC::PLAY_SPIN_SPD;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			inc = GDC::PLAY_SPIN_SPD;
		//a bit of physics degress per seconds X seconds for smooth predictable rate of rotation
		SetDegrees(GetDegrees() + inc * Application::GetElapsedSecs());
	}
	else
		mWaitSecs -= Application::GetElapsedSecs();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		
		//fire the ball here
		Vec2f newpos(GetPos().x - 50, GetPos().y - 26); //new position relative to angle 0 of the gun



		ball.SetPos(
			Vec2f(
				cos(GetDegrees()*0.01745329252) * (newpos.x-GetPos().x) - sin(GetDegrees()*0.01745329252) * (newpos.y - GetPos().y) + GetPos().x	//new x co ord relative to current angle
				,
				sin(GetDegrees()*0.01745329252) * (newpos.x - GetPos().x) + cos(GetDegrees()*0.01745329252) * (newpos.y - GetPos().y) + GetPos().y	//new y co ord relative to current angle
				));


		ball.SetVel(
			Vec2f(
				ball.GetPos().x - (cos(GetDegrees()*0.01745329252) * ((GetPos().x-10) - GetPos().x) - sin(GetDegrees()*0.01745329252) * ((GetPos().y - 5) - GetPos().y) + GetPos().x)	//new vel x co ord relative to current angle and centre offset
				,
				ball.GetPos().y - (sin(GetDegrees()*0.01745329252) * ((GetPos().x - 10) - GetPos().x) + cos(GetDegrees()*0.01745329252) * ((GetPos().y - 5) - GetPos().y) + GetPos().y)	//new vel y co ord relative to current angle and centre offset
			)*4); //multiplying to increase the velocity


		mWaitSecs = GDC::FIRE_DELAY;
	}
}