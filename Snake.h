#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	class Direction
	{
		public:
			double x,y;
			Direction(double xx,double yy):x(xx),y(yy){}
	};

class Snake
{
public:
	Snake();

	void handleInput(const sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	int checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;
	unsigned getscores()const {return scores;}
	unsigned getSize() const;

private:
	void move();
	void grow();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	Direction goal(const sf::Vector2f&x,const sf::Vector2i&y);//根据蛇头的位置和鼠标点击的位置确认direction
	bool ok(const Direction&a,const Direction&y);
	bool hitSelf_;

	sf::Vector2f position_;
	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;
	int scores;
	static const int InitialSize;
};
}

#endif