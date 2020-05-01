#pragma once
#include"stdafx.h"
#include"Game.h"
#include"State.h"
#include"NameInput.h"
#include"End.h"
/*
Game manager for a dice gambling game
*/
class GameManager
{
private:
	sf::RenderWindow window; 
	std::stack<State*> states; //top of the stack is the current state (NameInput, 
	//NumberInput, and End
	std::vector<sf::Text> lines; //the lines of text that are rendered 
	sf::Font font;
	sf::String playerName; 
	sf::String numInput;	//The number of goes the player wants 
	sf::Event sfEvent;		//input of the player
	int score;				//players individual total score
	//load the font the game uses
	void fontSetup();		
	//setup the game window
	void windowSetup();
	//get player input 
	void sfEventUpdate();
	//update the current state
	void update();
	//render the current state
	void render();
	//set the state the game starts at
	void startState();
	//initiate the next scene
	//sceneNum - the int value of the next scene (1 or 2)
	void nextScene(const int& sceneNum);
	//start the NumberInput scene to get the number goes the player wants
	void numScene();
	//set the position of all the text lines that are being rendered
	void sortLines();
	//start the game
	void rollDice();
public:
	//call functions to setup the font, window and the state the game starts at
	GameManager();
	//the game loop
	void start();
};

