#include "gameManager.h"

gameManager::gameManager() : digClock(correctTime)
{
	srand((unsigned)time(NULL));

}

void gameManager::updateInput(const WPARAM& wparam)
{

	switch (wparam)
	{
	case '1':
	case '2':
	case '3':
		if(state == State::Playing)
			checkIfCorrect(wparam);
		break;
	case 'Y':
	case 'y':
		if (state == State::Limbo)
		{
			setClocks();
			state = State::Playing;
		}
		break;
	case 'N':
	case 'n':
		if(state== State::Limbo)
			PostQuitMessage(0);
		break;



	}
}

void gameManager::Init(MyD3D& d3d)
{
	gpSpriteBatch = new DirectX::SpriteBatch(&d3d.GetDeviceCtx());
	font = new DirectX::SpriteFont(&d3d.GetDevice(), L"../bin/data/retro.spritefont");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "clock_face.dds");
	d3d.GetCache().LoadTexture(&d3d.GetDevice(), "clock_hands.dds");
	digClock.init(d3d);
	anClocks->push_back(new AnClock(1, DirectX::SimpleMath::Vector2(0, 200),d3d));
	anClocks->push_back(new AnClock(2, DirectX::SimpleMath::Vector2(300, 200),d3d));
	anClocks->push_back(new AnClock(3, DirectX::SimpleMath::Vector2(600, 200),d3d));
	setClocks();
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		deltaTime = WinUtil::Get().EndLoop(canUpdateRender);
		update();
		render(d3d);
	}

}
void gameManager::update()
{
	digClock.update(deltaTime);
	for (int i = 0; i < 3; i++)
		anClocks->at(i)->update(deltaTime);
}

void gameManager::render(MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();
	DirectX::SimpleMath::Vector4 colour{ 0.0f, 0.0f, 0.0f, 1.0f }; //black background
	d3d.BeginRender(colour);
	DirectX::CommonStates dxstate(&d3d.GetDevice());
	gpSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &d3d.GetWrapSampler());



	font->DrawString(gpSpriteBatch, "Time to play?", topTextPos);
	if(state == State::Playing)
		font->DrawString(gpSpriteBatch, "Which clock shows the same time as the digital one? 1, 2, or 3", bottomTextPos);
	else
		font->DrawString(gpSpriteBatch, (correctAnswer==true ? "correct, try again? <y or n>" : "wrong, try again?  <y or n>"), bottomTextPos);


	digClock.render(d3d, gpSpriteBatch);
	for (int i = 0; i < 3; i++)
		anClocks->at(i)->render(d3d, gpSpriteBatch);

	gpSpriteBatch->End();
	d3d.EndRender();
}

void gameManager::setClocks()
{
	correctTime.setRandTime();

	int newCorrectClock = (rand() % 3);
	for(int i=0; i<3;i++)
		if (i == newCorrectClock)
		{
			anClocks->at(i)->setNewTime(correctTime);
		}
		else
		{
			anClocks->at(i)->setNewTime();
		}
}

void gameManager::checkIfCorrect(const int code)
{
	int clockNum = 0;
	switch (code)
	{
	case '1':
		clockNum = 0;
		break;
	case '2':
		clockNum = 1;
		break;
	case '3':
		clockNum = 2;
		break;
	default:
		break;
	}
	state = State::Limbo;
	if ((anClocks->at(clockNum)->getTime().getHours() == correctTime.getHours()) && (anClocks->at(clockNum)->getTime().getMinutes() == correctTime.getMinutes()))
	{
		correctAnswer = true;
	}
	else
	{
		correctAnswer = false;
	}
}