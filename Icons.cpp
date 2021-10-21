#include "Icons.h"

/*
constructors for build and paint the icons 
@input: cordinate (x,y) , num of type , the window , the size of the object to paint
*/
Icons::Icons(double x, double y, int num, sf::RenderWindow& window, double width, double height)
:m_icons(sf::Vector2f(width, height))
{
	sf::Texture text[8];

	text[0].loadFromFile("icons/wall.png");
	text[1].loadFromFile("icons/robot.png");
	text[2].loadFromFile("icons/guard.png");
	text[3].loadFromFile("icons/door.png");
	text[4].loadFromFile("icons/rock.png");
	text[5].loadFromFile("icons/delete.png");
	text[6].loadFromFile("icons/clear.png");
	text[7].loadFromFile("icons/save.png");

	for (int i = 0; i < 8; i++) {
		if (num == i)
			m_icons.setTexture(&text[i]);
	}
	
	m_icons.setPosition(x, y);
	window.draw(m_icons);
}

/*
constructors for build and paint the icons
@input: array that represent cordinate and type , the window , the size of the board to paint (rows and cols)
*/
Icons::Icons(double *genArr, sf::RenderWindow& window, double cols, double rows,int count)
	:m_icons(sf::Vector2f(980.0 / cols, 670.0 / rows))
{
	sf::Texture text[8];

	text[0].loadFromFile("icons/wall.png");
	text[1].loadFromFile("icons/robot.png");
	text[2].loadFromFile("icons/guard.png");
	text[3].loadFromFile("icons/door.png");
	text[4].loadFromFile("icons/rock.png");
	text[5].loadFromFile("icons/delete.png");
	text[6].loadFromFile("icons/clear.png");
	text[7].loadFromFile("icons/save.png");

	for (int j = 0; j < count; j += 3) {
		// cout << "1" << endl;
		if (genArr[j] != NULL)
		{
			m_icons.setPosition(genArr[j], genArr[j + 1]);
			m_icons.setTexture(&text [int(genArr[j + 2])] );
			window.draw(m_icons);
		}
		
	}
}
