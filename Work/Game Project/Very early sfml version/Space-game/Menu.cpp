#include"phf.h"
#include "Menu.h"
#include "LevelOne.h"

void Menu::fontSetup()
{
  if (!font.loadFromFile("Fonts/Market_Deco.ttf"))
    throw("error loading font");
}

void Menu::backgroundSetup()
{
  if (!backgroundTex.loadFromFile("Textures/background.jpg"))
    throw("error finding background image");
  background.setTexture(&backgroundTex);
  background.setSize(sf::Vector2f(1920,1080));//TODO change to suit res
  background.setPosition(0, 0);
}

void Menu::guiSetup()
{
  for (int i(0); i < 3;i++)
  {
    menu[i].setFont(font);
    menu[i].setFillColor(sf::Color::White);
    menu[i].setPosition(sf::Vector2f(1920-((1920.f / 20.f)*19), 1080.f / 4.f * (i+1.f)));
  }
  menu[0].setString("Play");
  menu[1].setString("Options");
  menu[2].setString("Exit");
  selected = 0;
}

Menu::Menu(sf::RenderWindow* window, std::deque<State*>* states)
{
  this->states = states;
  this->window = window;
  timeout = 0.1f;
  backgroundSetup();
  fontSetup();
  guiSetup();
  colourChange();
}

void Menu::update(const float& deltaTime)
{
  updateInput(deltaTime);
  timeout -= deltaTime;
}

void Menu::render()
{
  window->draw(background);
  for (int i(0); i < 3; i++)
    window->draw(menu[i]);
}

void Menu::updateInput(const float& deltaTime)
{
  if (timeout <= 0)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      moveUp();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      moveDown();
    timeout = 0.1f;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    switch (selected)
    {
    case 0:
      states->push_front(new LevelOne(window, states));
      break;
    case 1:
      //TODO settings menu
      break;
    case 2:
      window->close();
      break;
    default:
      break;
    }
  }
}

void Menu::moveUp()
{
  if (selected - 1 >= 0)
    selected--;
  colourChange();
}

void Menu::moveDown()
{
  if (selected + 1 < 3)
    selected++;
  colourChange();
}

void Menu::colourChange()
{
  for (int i(0); i < 3;i++)
    if (i == selected)
      menu[i].setFillColor(sf::Color::Red);
    else
      menu[i].setFillColor(sf::Color::White);
}