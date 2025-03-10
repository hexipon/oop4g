#pragma once
#include"State.h"
#include"Text.h"
#include"Sprite.h"
class Pause : public State
{
public:
	Pause(d3d& d3d_, DirectX::SpriteBatch& spriteBatch_, float& deltaTime_) :
		State(d3d_, spriteBatch_, deltaTime_), gameName(_d3d, "retro.spritefont"), background(_d3d)
	{
		for (int i = 0; i < menuSize; i++)
			menuItems->push_back(Text(_d3d, "retro.spritefont"));
		gameName.setString("Untitled Space Game");
		gameName.SetColour(Colours::Green);
		gameName.SetRotation(-0.3f);
		menuItems->at(Continue).setString("Continue");
		menuItems->at(Continue).SetColour(Colours::Green);
		menuItems->at(Menu).setString("Exit To Main Menu");
		menuItems->at(Exit).setString("Exit To Windows");
		background.SetTex(*_d3d.GetCache().Get("PauseBackground").pTex);
		sizeSetup();
		background.setColour(DirectX::SimpleMath::Vector4(1,1,1,0.75f));
	}
	~Pause() {
		menuItems->clear();
	}
	void update() override;
	void render() override;
	void sizeSetup() override;
	const void enterPressed();
	const void upPressed();
	const void downPressed();
	const void colourChange();
private:
	Text gameName;
	const enum menuOption { Continue, Menu, Exit };
	static const int menuSize = 3;
	std::vector<Text> menuItems[menuSize];
	const float selectionChangeCooldown = 0.2f;
	float selectionChangeCooldownTimer = 0.f;
	menuOption currentlySelected = Continue;
	Sprite background;
};

