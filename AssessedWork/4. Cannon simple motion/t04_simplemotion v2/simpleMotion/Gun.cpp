#include "Gun.h"
#include"Application.h"
void Gun::Update()
{
	if (WaitSecs <= 0)
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
		WaitSecs -= Application::GetElapsedSecs();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		
		//fire the ball here
		Vec2f newpos(GetPos().x +X_Offset, GetPos().y +Y_Offset); //new position relative to angle 0 of the gun



		ball.SetPos(
			Vec2f(
				cos(GetDegrees()*GDC::DegToRadConversion) * 
				(newpos.x-GetPos().x) - sin(GetDegrees()*GDC::DegToRadConversion) * 
				(newpos.y - GetPos().y) + 
				GetPos().x	//new x co ord relative to current angle
				,
				sin(GetDegrees()*GDC::DegToRadConversion) * 
				(newpos.x - GetPos().x) + cos(GetDegrees()*GDC::DegToRadConversion) * 
				(newpos.y - GetPos().y) +
				GetPos().y	//new y co ord relative to current angle
				));


		ball.SetVel(
			Vec2f(
				ball.GetPos().x - 
				(cos(GetDegrees()*GDC::DegToRadConversion) * 
					((GetPos().x+Ball_X_Offset) - GetPos().x) - 
					sin(GetDegrees()*GDC::DegToRadConversion) * 
					((GetPos().y + Ball_Y_Offset) - GetPos().y) + 
					GetPos().x)	//new vel x co ord relative to current angle and centre offset
				,
				ball.GetPos().y - 
					(sin(GetDegrees()*GDC::DegToRadConversion) * 
					((GetPos().x +Ball_X_Offset) - GetPos().x) + 
					cos(GetDegrees()*GDC::DegToRadConversion) * 
					((GetPos().y +Ball_Y_Offset) - GetPos().y) + 
					GetPos().y)	//new vel y co ord relative to current angle and centre offset
			)*4); //multiplying to increase the velocity


		WaitSecs = GDC::FIRE_DELAY;
	}
}