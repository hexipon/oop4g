#pragma once
#include"State.h"
#include"FontCache.h"
#include"Text.h"
#include"gameData.h"
#include"Sprite.h"
class Settings : public State
{
public:

	Settings(d3d& d3d_, DirectX::SpriteBatch& spriteBatch_, float& deltaTime_) :
		State(d3d_, spriteBatch_, deltaTime_), gameName(_d3d, "retro.spritefont"), background(_d3d)
	{
		for (int i = 0; i < menuSize; i++)
			menuItems->push_back(Text(_d3d, "retro.spritefont"));
		menuItems->at(Resolution).SetColour(Colours::Green);
		menuItems->at(Back).setString("Back");
		menuItems->at(Comfirm).setString("Comfirm");
		menuItems->at(Exit).setString("Exit");
		background.SetTex(*_d3d.GetCache().Get("staticBackground").pTex);
		//get current res
		for (unsigned int i = 0; i < resolutions->Length(); i++)
			if (resolutions[i].x == gameData::Get().WindowSize.x)
				selectedRes = resolution(i);
		menuItems->at(Resolution).setString(("Resolution:" + std::to_string((int)resolutions[selectedRes].x) + "x" + std::to_string((int)resolutions[selectedRes].y)).c_str());

		sizeSetup();
	}
	~Settings() {
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
	const enum menuOption { Resolution, Comfirm, Back, Exit };

	const DirectX::SimpleMath::Vector2 resolutions[9] = { {768,432},{896,504},{1024,576},{1152,648},{1280,720},{1408,792},{1536,864},{1664,936},{1792,1008} };

	const enum resolution { w768, w896, w1024, w1152, w1280, w1408, w1536, w1664, w1792};
	resolution selectedRes;
	static const int menuSize = 4;
	Text gameName;
	std::vector<Text> menuItems[menuSize];
	const float selectionChangeCooldown = 0.2f;
	float selectionChangeCooldownTimer = 0.f;
	menuOption currentlySelected = Resolution;
	const void changeRes();
	Sprite background;

};

