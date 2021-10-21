#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Icons
{
public: 
	/* Icons(int num, sf::RenderWindow& window);
	sf::RectangleShape m_icon; */
	Icons(double x, double y, int num, sf::RenderWindow& window, double width, double height);
	sf::RectangleShape m_icons;
	Icons(double *genArr, sf::RenderWindow& window, double cols, double rows, int count);
};

