#pragma once
//keep important shared information "GameData" in one accessible object and pass it around
//note - structs are like classes but everything is always public, so best kept just for data
struct GD
{
	sf::Font font;				//a shared font to use everywhere
	sf::RenderWindow *pWindow;	//can't render anything without this
	std::string playerName;			//the player's name is needed by different objects
};