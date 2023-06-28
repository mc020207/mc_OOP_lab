#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "SettingScreen.h"
#include "GameOverScreen.h"
using namespace sfSnake;
SettingScreen::SettingScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	problems_.setFont(font_);
	problems_.setString(
		"1.background color"
        "\n\n\n\n2.need grid lines?"
        "\n\n\n\n3.grid lines's color"
        "\n\n\n\npress [Enter] to save");
    problems_.setFont(font_);
    problems_.setColor(sf::Color::Red);
    answers_[0].setString("[Q]Black");
    answers_[1].setString("[W]White");
    answers_[2].setString("[E]Brown");
    answers_[3].setString("[A]Yes");
    answers_[4].setString("[S]No");
    answers_[5].setString("[Z]Black");
    answers_[6].setString("[X]White");
    answers_[7].setString("[C]Brown");
    answers_[0].setPosition(sf::Vector2f(0,60));
    answers_[1].setPosition(sf::Vector2f(210,60));
    answers_[2].setPosition(sf::Vector2f(420,60));
    answers_[3].setPosition(sf::Vector2f(0,180));
    answers_[4].setPosition(sf::Vector2f(210,180));
    answers_[5].setPosition(sf::Vector2f(0,300));
    answers_[6].setPosition(sf::Vector2f(210,300));
    answers_[7].setPosition(sf::Vector2f(420,300));
    for (int i=0;i<8;i++){
        answers_[i].setFont(font_);
        answers_[i].setColor(sf::Color::Blue);
    } 
}

void SettingScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            Game::Screen = std::make_shared<MenuScreen>();
        int i;
        for (i=0;i<3&&answers_[i].getColor()!=sf::Color::Green;i++);
        switch (i)
        {
            case 0: Game::backRGB=sf::Color::Black;break;
            case 1: Game::backRGB=sf::Color::White;break;
            case 2: Game::backRGB=sf::Color(128,64,0);break;
        }
        for (i=3;i<5&&answers_[i].getColor()!=sf::Color::Green;i++);
        switch (i)
        {
            case 3: Game::grid_lines=true;break;
            case 4: Game::grid_lines=false;return;
        }
        for (i=5;i<8&&answers_[i].getColor()!=sf::Color::Green;i++);
        switch (i)
        {
            case 6: Game::lines_color=sf::Color(255,255,255,64);break;
            case 5: Game::lines_color=sf::Color(0,0,0,64);break;
            case 7: Game::lines_color=sf::Color(128,64,0,64);break;
        }
    }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        answers_[0].setColor(sf::Color::Green);
        answers_[1].setColor(sf::Color::Blue);
        answers_[2].setColor(sf::Color::Blue);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        answers_[1].setColor(sf::Color::Green);
        answers_[0].setColor(sf::Color::Blue);
        answers_[2].setColor(sf::Color::Blue);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        answers_[2].setColor(sf::Color::Green);
        answers_[1].setColor(sf::Color::Blue);
        answers_[0].setColor(sf::Color::Blue);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        answers_[3].setColor(sf::Color::Green);
        answers_[4].setColor(sf::Color::Blue);
        for (int i=5;i<8;i++){
            answers_[i].setColor(sf::Color::Blue);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        answers_[4].setColor(sf::Color::Green);
        answers_[3].setColor(sf::Color::Blue);
        for (int i=5;i<8;i++){
            answers_[i].setColor(sf::Color(192,192,192));
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        if (answers_[5].getColor()==sf::Color(192,192,192)) return;
        answers_[5].setColor(sf::Color::Green);
        answers_[6].setColor(sf::Color::Blue);
        answers_[7].setColor(sf::Color::Blue);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        if (answers_[5].getColor()==sf::Color(192,192,192)) return;
        answers_[6].setColor(sf::Color::Green);
        answers_[5].setColor(sf::Color::Blue);
        answers_[7].setColor(sf::Color::Blue);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
        if (answers_[5].getColor()==sf::Color(192,192,192)) return;
        answers_[7].setColor(sf::Color::Green);
        answers_[6].setColor(sf::Color::Blue);
        answers_[5].setColor(sf::Color::Blue);
    }
}

void SettingScreen::update(sf::Time delta)
{
	// static bool movingLeft = false;
	// static bool movingRight = true;

	// if (movingRight)
	// {
	// 	snakeText_.rotate(delta.asSeconds());

	// 	if (static_cast<int>(snakeText_.getRotation()) == 10)
	// 	{
	// 		movingRight = false;
	// 		movingLeft = true;
	// 	}
	// }

	// if (movingLeft)
	// {
	// 	snakeText_.rotate(-delta.asSeconds());

	// 	if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
	// 	{
	// 		movingLeft = false;
	// 		movingRight = true;
	// 	}
	// }
}

void SettingScreen::render(sf::RenderWindow& window)
{
	window.draw(problems_);
	for (int i=0;i<8;i++){
        window.draw(answers_[i]);
    }
}