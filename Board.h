#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Button.h"
#include  <iostream>
#include "Icons.h"
#include <iostream>
#include <fstream>
using namespace std;
class Board
{
public:

	Board();
	int getSize(std::string sub);
	void printBoard(int rows, int cols, sf::RenderWindow& window);

private:

	int m_width;
	int m_height;
	int checkMenu(double y);
	double checkRow(int rows, int y);
	double checkCol(int cols, int x);
	void clearBoard(double *arr,int count);
	void save(std::ofstream &myboard, int genCount, int cols, double * genArr);



};

