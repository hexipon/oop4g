#pragma once
#include"State.h"
#include"FontCache.h"
#include"Text.h"
#include"gameData.h"
#include"Sprite.h"

class Manager;
class Instructions : public State
{
public:
	Instructions(d3d& d3d_, DirectX::SpriteBatch& spriteBatch_, float& deltaTime_) :
		State(d3d_, spriteBatch_, deltaTime_), gameName(_d3d, "retro.spritefont"), background(_d3d)
	{
		for (int i = 0; i < menuSize; i++)
			menuItems->push_back(Text(_d3d, "retro.spritefont"));
		gameName.setString("Untitled Space Game");
		gameName.SetColour(Colours::Green);
		gameName.SetRotation(-0.3f);
		menuItems->at(Back).setString("Back");
		menuItems->at(Back).SetColour(Colours::Green);
		menuItems->at(Exit).setString("Exit");
		background.SetTex(*_d3d.GetCache().Get("staticBackground").pTex);
		sizeSetup();
	}
	~Instructions() {
		menuItems->clear();
	}
	void update() override;
	void render() override;
	void sizeSetup() override;
	const void enterPressed();
private:
	Text gameName;
	const enum menuOption { Back, Exit };
	static const int menuSize = 2;
	std::vector<Text> menuItems[menuSize];
	const float selectionChangeCooldown = 0.2f;
	float selectionChangeCooldownTimer = 0.f;
	menuOption currentlySelected = Back;
	Sprite background;
};

