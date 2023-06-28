#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include<iostream>
using namespace sfSnake;
static std::default_random_engine engine;

GameScreen::GameScreen() : snake_()
{
	engine.seed(time(NULL));
	for (int i=0;i<2;i++){
		for (int j=0;j<3;j++) generateFruit(i);
	}
	for (int i=2;i<5;i++){
		for (int j=0;j<6;j++) generateFruit(i);
	}
	//std::cout<<2;
	if (Game::grid_lines==false) return;
	for (int i=0;i<Game::Width;i+=SnakeNode::radius_*2){
		lines.push_back(sf::Vertex(sf::Vector2f(i,0),sf::Color(Game::lines_color)));
		lines.push_back(sf::Vertex(sf::Vector2f(i,Game::Height),sf::Color(Game::lines_color)));
	}
	for (int i=0;i<Game::Height;i+=SnakeNode::radius_*2){
		lines.push_back(sf::Vertex(sf::Vector2f(0,i),sf::Color(Game::lines_color)));
		lines.push_back(sf::Vertex(sf::Vector2f(Game::Width,i),sf::Color(Game::lines_color)));
	}
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	snake_.update(delta);
	int i=snake_.checkFruitCollisions(fruit_);
	if (i<5) {
		generateFruit(i);
		//std::cout<<i;
	}
	if (snake_.hitSelf()){
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getscores());
	}
		
}

void GameScreen::render(sf::RenderWindow& window)
{
	if (Game::grid_lines){
		window.draw(&lines[0],lines.size(),sf::Lines);
	}
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
	//std::cout<<fruit_.size();
}

void GameScreen::generateFruit(int i)
{
	//std::cout<<1;
	static std::uniform_int_distribution<int> xDistribution(SnakeNode::radius_*2, Game::Width - SnakeNode::radius_*2);
	static std::uniform_int_distribution<int> yDistribution(SnakeNode::radius_*2, Game::Height - SnakeNode::radius_*2);
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),i));
}

