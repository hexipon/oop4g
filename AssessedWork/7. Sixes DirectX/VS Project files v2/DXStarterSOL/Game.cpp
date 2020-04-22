#include"Game.h"
#include "D3DUtil.h"

void Game::nextScene(MyD3D& d3d, const int & sceneNum)
{

	switch (sceneNum)
	{
	case 1:
		numScene(d3d);
		break;
	case 2:
		if (!(numInput.length() < 1))
			rollDice(d3d);
		break;
	default:
		break;
	}
}

void Game::rollDice(MyD3D& d3d)
{
	std::string baseString;
	const int goes = stoi(numInput);
	DiceGame dGame;
	score = dGame.play(goes, lines);
	states.pop();
	lines.push_back(baseString);
	states.push(new End(d3d, lines[lines.size() - 1], playerName, score));

}

void Game::numScene(MyD3D& d3d)
{
	std::string baseString;
	lines.push_back(baseString);
	states.pop();
	states.push(new NumberInput(d3d, lines[1], numInput));
}
void Game::init(MyD3D& d3d)
{
	gColours[0] = Colours::White;
	gColours[1] = Colours::Black;
	gColours[2] = Colours::Red;
	gColours[3] = Colours::Green;
	gColours[4] = Colours::Blue;
	gColours[5] = Colours::Yellow;
	gColours[6] = Colours::Cyan;
	gColours[7] = Colours::Magenta;

	gpSpriteBatch = new DirectX::SpriteBatch(&d3d.GetDeviceCtx());
	assert(gpSpriteBatch);

	//start state
	std::string baseString;
	lines.push_back(baseString);
	states.push(new NameInput(d3d, lines.front(), playerName));

	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender)
		{
			UpdateAndRender(d3d);
		}
	}
	ReleaseGame();
}

void Game::UpdateAndRender(MyD3D& d3d) //update and render
{
	//update
	gameTime += deltaTime;
	if (gameTime > 0.5f)
	{
		gCycle++;
		if (gCycle >= 8)
			gCycle = 0;
		gameTime = 0;
	}
	states.top()->update();


	//render
	WinUtil& wu = WinUtil::Get();
	float alpha = (float)wu.GetData().clientWidth / (1024 - wu.GetData().minClientWidth);
	if (alpha > 1)
		alpha = 1;
	DirectX::SimpleMath::Vector4 colour = Colours::Black;
	d3d.BeginRender(colour);
	gpSpriteBatch->Begin();
	//render stuff

	float ypos(0.f);
	DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0, 0);
	for (size_t i(lines.size() >= 24 ? (lines.size() - 24) : 0); i < lines.size(); i++)
	{

		pos.y=ypos;
		DirectX::SpriteFont font(&d3d.GetDevice(), L"../bin/data/retro.spritefont");
		font.DrawString(gpSpriteBatch, lines[i].c_str(), pos);
		ypos += 32.f;
	}

	gpSpriteBatch->End();
	d3d.EndRender();


	deltaTime = WinUtil::Get().EndLoop(canUpdateRender);
}


void Game::ReleaseGame()
{
	delete gpSpriteBatch;
	gpSpriteBatch = nullptr;
}