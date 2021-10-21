#include "Menu.h"


/*
build and paint the menu area
*/
Menu::Menu(sf::RenderWindow& window)
{
	sf::RectangleShape bg_menu(sf::Vector2f(225, 670));
	bg_menu.setFillColor(sf::Color(0,170,160));
	bg_menu.setPosition(25, 25);
	window.draw(bg_menu);
}

