#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::radius_= 10.f;
SnakeNode::SnakeNode(sf::Vector2f position,int i,double angle)
: position_(position),angle_(angle)
{
	texture.loadFromFile("fruits/dog.png");
	shape_.setPosition(position_);
	shape_.setFillColor(fillcolor[i]);
	shape_.setRadius(SnakeNode::radius_);
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(-1.f);
	shape2_.setSize(sf::Vector2f(SnakeNode::radius_*24/13,SnakeNode::radius_*10/13));
	shape2_.setPosition(sf::Vector2f(position.x+SnakeNode::radius_*1/13,position.y+SnakeNode::radius_*8/13));
	shape2_.setFillColor(fillcolor[3-i]);
	sf::FloatRect shape_Bounds = shape_.getLocalBounds();
	shape_.setOrigin(shape_Bounds.left + shape_Bounds.width / 2,
	shape_Bounds.top + shape_Bounds.height / 2);

	sf::FloatRect shape2_Bounds = shape2_.getLocalBounds();
	shape2_.setOrigin(shape2_Bounds.left + shape2_Bounds.width / 2,
	shape2_Bounds.top + shape2_Bounds.height / 2);
}
SnakeNode::SnakeNode(sf::Vector2f position,int k,int i)
: position_(position)
{
	texture.loadFromFile("fruits/dog.png");
	shape_.setPosition(position_);
	shape_.setRadius(SnakeNode::radius_);
	shape_.setTexture(&texture);
	shape2_.setSize(sf::Vector2f(0.01,0.01));
	shape2_.setPosition(sf::Vector2f(position.x+SnakeNode::radius_*1/13,position.y+SnakeNode::radius_*8/13));
	shape2_.setFillColor(sf::Color::White);
	sf::FloatRect shape_Bounds = shape_.getLocalBounds();
	shape_.setOrigin(shape_Bounds.left + shape_Bounds.width / 2,
	shape_Bounds.top + shape_Bounds.height / 2);

	sf::FloatRect shape2_Bounds = shape2_.getLocalBounds();
	shape2_.setOrigin(shape2_Bounds.left + shape2_Bounds.width / 2,
	shape2_Bounds.top + shape2_Bounds.height / 2);
}
void SnakeNode::setPosition(sf::Vector2f position,double angle)
{
	position_ = position;
	angle_=angle;
	shape_.setPosition(position_);
	shape2_.setPosition(position_);
}
void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
	shape2_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset,double angle)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
	shape2_.setPosition(position_);
	angle_=angle;
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window,int k)
{
	//sf::Texture texture;
	//texture.loadFromFile("fruits/dog.png");
	shape_.setRotation(angle_);
	shape_.setTexture(&texture);
	window.draw(shape_);
}
void SnakeNode::render(sf::RenderWindow& window)
{
	shape_.setRotation(angle_);
	shape2_.setRotation(angle_);
	window.draw(shape_);
	window.draw(shape2_);
}