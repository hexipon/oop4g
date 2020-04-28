#pragma once
#include"State.h"
#include"Vec2f.h"
class _Menu : public State
{
public:
	static const enum menutype { start, player1wins, player2wins };
	_Menu(sf::RenderWindow& _window, float& _deltaTime, menutype _mtype);
	void update() override {}
	void render() override;
	void updateInput(sf::Event & event) override;
private:
	menutype& mtype;
	sf::Texture backgroundTex;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text menu[2];
	int selected;
	void fontSetup();
	void backgroundSetup();
	void guiSetup();
	void moveUp();
	void moveDown();
	void colourChange();
};

