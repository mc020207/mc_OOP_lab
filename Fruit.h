#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <iostream>
namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position, int i);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
	int getcolorrank() const {return colorrank;}
private:
	sf::CircleShape shape_;
	sf::Texture texture;
	std::string str[5] = {"0","1","2","3","4"};
	int colorrank;
	static const float Radius;
};
}

#endif