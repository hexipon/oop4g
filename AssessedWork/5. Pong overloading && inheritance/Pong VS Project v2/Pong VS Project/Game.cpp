#include "Game.h"
#include"Ball.h"
#include"GameManager.h"
_Game::_Game(sf::RenderWindow& _window, float& _deltaTime) :
	State(_window, _deltaTime), player1(ball, Walls), player2(ball, Walls), Walls{ Wall(ball,Wall::TOP),Wall(ball,Wall::BOTTOM) }
{
	//setup text
	text.setString("First to 6 wins!");
	text.setFont("../Fonts/Market_Deco.ttf");
	text.SetSize(GameData::SCREEN_RES.y*GameData::SCORE_FONT_SIZE*.4f);
	text.SetPos(Vec2f((GameData::SCREEN_RES.x / 2) - (text.getGlobalBounds().width/2)*0.9f, GameData::SCREEN_RES.y*.001f)); //the 0.9f is to make it look more centred 


	//setup walls
	Walls[Wall::TOP].SetColour(sf::Color::Blue);
	Walls[Wall::TOP].SetSize(Vec2f(GameData::SCREEN_RES.x, (GameData::SCREEN_RES.y*GameData::WALL_WDITH)));
	Walls[Wall::TOP].SetPos(Vec2f{ 0,0 });
	Walls[Wall::BOTTOM].SetColour(sf::Color::Blue);
	Walls[Wall::BOTTOM].SetSize(Vec2f(GameData::SCREEN_RES.x, (GameData::SCREEN_RES.y*GameData::WALL_WDITH)));
	Walls[Wall::BOTTOM].SetPos(Vec2f{0,GameData::SCREEN_RES.y*(1 - GameData::WALL_WDITH) });

	//setup player 1 paddle
	player1.SetSize(Vec2f(GameData::SCREEN_RES.x*GameData::PADDLE_WIDTH, GameData::SCREEN_RES.y*GameData::PADDLE_HEIGHT));
	player1.SetPos(Vec2f(GameData::SCREEN_RES.x*GameData::PADDLE_WIDTH, GameData::SCREEN_RES.y/2));
	player1.SetColour(sf::Color::Red);
	player1.setPlayerNum(1);
	//setup player 2 paddle
	player2.SetSize(Vec2f(GameData::SCREEN_RES.x*GameData::PADDLE_WIDTH, GameData::SCREEN_RES.y*GameData::PADDLE_HEIGHT));
	player2.SetPos(Vec2f(GameData::SCREEN_RES.x*(1-GameData::PADDLE_WIDTH*2), GameData::SCREEN_RES.y / 2));
	player2.SetColour(sf::Color::Red);
	player2.setPlayerNum(2);

	//setup ball
	ball.SetSize(GameData::BALL_SIZE*GameData::SCREEN_RES.y);
	ball.SetColour(sf::Color::Red);
	ball.SetPos(GameData::SCREEN_RES / 2.f);

	//setup scores
	Score::player1Score().resetScore();
	Score::player1Score().setFont("../Fonts/Market_Deco.ttf");
	Score::player1Score().SetSize(GameData::SCREEN_RES.y*GameData::SCORE_FONT_SIZE);
	Score::player1Score().SetPos(Vec2f((GameData::SCREEN_RES.x / 2) - (Score::player1Score().getGlobalBounds().width/2)*5.f, GameData::SCREEN_RES.y*.1f));
	Score::player2Score().resetScore();
	Score::player2Score().setFont("../Fonts/Market_Deco.ttf");
	Score::player2Score().SetSize(GameData::SCREEN_RES.y*GameData::SCORE_FONT_SIZE);
	Score::player2Score().SetPos(Vec2f((GameData::SCREEN_RES.x / 2) + (Score::player2Score().getGlobalBounds().width/2)*5.f, GameData::SCREEN_RES.y*.1f));

}

void _Game::updateInput(sf::Event & event)
{
	switch (playState)
	{
	case PlayState::ballOnPaddle:
		

	if (event.key.code == sf::Keyboard::Space)
	{
		ball.resetSpeedModifier();
		float x, y;
		if (ball.GetPos().x > (window.getSize().x / 2))
			x = -GameData::ballSpeed;
		else
			x = GameData::ballSpeed;
		if (ball.GetPos().y > (window.getSize().y / 2))
			y = GameData::ballSpeed;
		else
			y = -GameData::ballSpeed;
		ball.SetVel(Vec2f(x, y));

		playState = PlayState::playing;
		ballOnPlayer1 = !ballOnPlayer1;
	}
		break;
	case PlayState::playing:
		break;
	default:
		break;
	}
}

void _Game::update()
{
	if (playState == PlayState::ballOnPaddle)
	{
		if (ballOnPlayer1)
			ball.SetPos(Vec2f(GameData::SCREEN_RES.x*(GameData::PADDLE_WIDTH*2),player1.GetPos().y-(GameData::BALL_SIZE*GameData::SCREEN_RES.y)+((GameData::SCREEN_RES.y*GameData::PADDLE_HEIGHT)/2)));
		if (!ballOnPlayer1)
			ball.SetPos(Vec2f(GameData::SCREEN_RES.x*(1 - (GameData::PADDLE_WIDTH * 3.15f)), player2.GetPos().y - (GameData::BALL_SIZE*GameData::SCREEN_RES.y) + ((GameData::SCREEN_RES.y*GameData::PADDLE_HEIGHT) / 2)));
	}
	ball.Update(deltaTime);
	player1.Update(deltaTime);
	player2.Update(deltaTime);
	for (int i = 0; i < Wall::MaxWalls; ++i)
		Walls[i].Update(deltaTime);

	if (ball.GetPos().x <player1.GetPos().x)
	{
		playState = PlayState::ballOnPaddle;
		Score::player2Score()++;
		round++;
	}
	if (ball.GetPos().x > player2.GetPos().x)
	{
		playState = PlayState::ballOnPaddle;
		Score::player1Score()++;
		round++;
	}
	if (round == 11 || Score::player1Score().getScore()==6 || Score::player2Score().getScore() == 6)
	{
		if (Score::player1Score().getScore() > Score::player2Score().getScore())
			GameManager::Instance().changeState(GameManager::stateNames::Player1Wins);
		else
			GameManager::Instance().changeState(GameManager::stateNames::Player2Wins);
	}
}

void _Game::render()
{
	ball.Render(window);
	player1.Render(window);
	player2.Render(window);
	Score::player1Score().Render(window);
	Score::player2Score().Render(window);
	for (int i = 0; i < Wall::MaxWalls; ++i)
		Walls[i].Render(window);
	text.Render(window);
}
