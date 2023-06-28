#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include<iostream>
using namespace sfSnake;

const float Fruit::Radius = 7.f;

Fruit::Fruit(sf::Vector2f position,int i):colorrank(i)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	texture.loadFromFile("fruits/"+str[colorrank]+".png");
	shape_.setTexture(&texture);
}

void Fruit::render(sf::RenderWindow& window)
{
	//texture.loadFromFile("fruits/"+str[colorrank]+".png");
	shape_.setTexture(&texture);
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}