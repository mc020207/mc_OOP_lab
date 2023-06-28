#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class SettingScreen : public Screen
{
public:
	SettingScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
private:
	sf::Font font_;
	sf::Text problems_;
	sf::Text answers_[8];
	int score_;
};
}
