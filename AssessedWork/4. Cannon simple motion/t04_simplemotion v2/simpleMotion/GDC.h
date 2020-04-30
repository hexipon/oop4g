#pragma once

#include<SFML/Graphics.hpp>
#include"Vec2i.h"
//a namespace is just another type of box with a label where we can group things together
//GDC="GameDataConstants" - a box for all your magic numbers
//especially those that a designer might need to tweak to balance the game
namespace GDC
{
	const Vec2i SCREEN_RES{ 1200,800 };	//desired resolution
	const char ESCAPE_KEY{ 27 };		//ASCII code
	const char ENTER_KEY{ 13 };
	const sf::Uint32 ASCII_RANGE{ 127 };//google an ASCII table, after 127 we don't care
	const float PLAY_SPIN_SPD{ 200.f };	//how fast to spin
	const float WALL_WDITH{ 0.1f };		//the walls skirt the edge of the screen
	const float GUN_LENGTH{ 70.f };		//from the centre to the end of the barrel
	const float BALL_SPEED{ 400.f };	//ball speed in units per sec
	const float FIRE_DELAY{ 0.25f };	//stop on firing for this time in secs
	const float CANNON_ROT_OFFSET{ 115 };	//when rotating the cannon, the barrel points at a specific angle (rotate anti-clockwise from horizontal)
	const float DegToRadConversion=0.01745329252f; //conversion rate of degress to radians
};