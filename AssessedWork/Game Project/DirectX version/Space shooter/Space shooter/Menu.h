#pragma once
#include"State.h"
#include"FontCache.h"
#include"Text.h"
#include"gameData.h"
#include"Sprite.h"

class Manager;
class Menu : public State
{
public:
	Menu(d3d& d3d_, DirectX::SpriteBatch& spriteBatch_, float& deltaTime_) : 
		State(d3d_,spriteBatch_,deltaTime_), gameName(_d3d,"retro.spritefont")
	{
		for(int i=0;i<menuSize;i++)
			menuItems->push_back(Text(_d3d, "retro.spritefont"));
		background->push_back(Sprite(_d3d));
		background->push_back(Sprite(_d3d));
		menuItems->at(Play).setString("Play");
		menuItems->at(Play).SetColour(Colours::Green);
		menuItems->at(Instructions).setString("Instructions");
		menuItems->at(Settings).setString("Settings");
		menuItems->at(Exit).setString("Exit");
		gameName.setString("Untitled Space Game");
		gameName.SetColour(Colours::Green);
		gameName.SetRotation(-0.3f);
		background->at(0).SetTex(*_d3d.GetCache().Get("star1alpha").pTex);
		background->at(1).SetTex(*_d3d.GetCache().Get("star2alpha").pTex);
		sizeSetup();
	}
	~Menu() {
		menuItems->clear();
	}
	void update() override;
	void render() override;
	void sizeSetup() override;
	const void enterPressed();
	const void upPressed();
	const void downPressed();
	const void changeColours();
private:
	const enum menuOption{ Play, Instructions, Settings, Exit};
	static const int menuSize = 4;
	Text gameName;
	std::vector<Text> menuItems[menuSize];
	std::vector<Sprite> background[2];
	const float selectionChangeCooldown = 0.2f;
	float selectionChangeCooldownTimer = 0.f;
	menuOption currentlySelected = Play;
};

