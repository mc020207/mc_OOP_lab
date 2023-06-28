#include <SFML/Graphics.hpp>
#include <random>
#include <memory>
#include <iostream>
#include <cmath>
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;
static std::default_random_engine engine1;
const int Snake::InitialSize = 5;
Direction Snake::goal(const sf::Vector2f&x,const sf::Vector2i&y){
	double x1=x.x,x2=y.x,y1=x.y,y2=y.y;
	if (x2<0||x2>Game::Width) return Direction(0,0);
	if (y2<0||y2>Game::Height) return Direction(0,0);
	double distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return Direction((x2-x1)/distance,(y2-y1)/distance);
}
bool Snake::ok(const Direction&a,const Direction&b){
	if (b.x==0&&b.y==0) return false;
	return a.x*b.x+a.y*b.y>=-1/2;
}
Snake::Snake() : direction_(Direction(0,-1)), hitSelf_(false)
{
	engine1.seed(time(NULL));
	initNodes();
	scores=InitialSize;
	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	int i=0;
	static std::uniform_int_distribution<int> fillcolor(0,3);
	nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::radius_ ,
			Game::Height / 2 - (SnakeNode::radius_) + ((SnakeNode::radius_) *2* i)),0,0));
	for (i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::radius_ ,
			Game::Height / 2 - (SnakeNode::radius_) + ((SnakeNode::radius_) *2* i)),fillcolor(engine1)));
	}
}

void Snake::handleInput(const sf::RenderWindow& window)
{
	Direction direction__(0,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction__.x=0,direction__.y=-1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction__.x=0,direction__.y=1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction__.x=-1,direction__.y=0;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction__.x=1,direction__.y=0;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		direction__=goal(nodes_[0].getPosition(),sf::Mouse::getPosition(window));
	}
	if (ok(direction_,direction__)){
		direction_=direction__;
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

int Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds())){
			toRemove = it;
			break;
		}
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		int k=toRemove->getcolorrank();
		for(int i=0;i<k-1;i++) grow();
		scores++;
		fruits.erase(toRemove);
		return k;
	}
	return 6;
}

void Snake::grow()
{
	static std::uniform_int_distribution<int> fillcolor(0,3);
	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,nodes_[nodes_.size() - 1].getPosition().y),fillcolor(engine1),nodes_[nodes_.size() - 1].getangle()));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			break;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_[i-1].getPosition(),nodes_[i-1].getangle());
	}
	double angle;
	if (direction_.y==0){
		if (direction_.x<0) angle=90;
		else angle=-90;
	}
	else if (direction_.y<0)
		angle=atan(-direction_.x/direction_.y)/3.14159265354*180;
	else 
		angle=180+atan(-direction_.x/direction_.y)/3.14159265354*180;
	nodes_[0].move(SnakeNode::radius_*2*direction_.x, SnakeNode::radius_*2*direction_.y,angle);
}

void Snake::render(sf::RenderWindow& window)
{
	nodes_[0].render(window,0);
	for (int i=1;i<nodes_.size();i++){
		nodes_[i].render(window);
	}
}