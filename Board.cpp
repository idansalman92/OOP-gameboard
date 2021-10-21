#include "Board.h"
#include <iostream>
#include <fstream>

using namespace std;

// sf::Color board_color(252, 244, 217);
sf::Color board_color(238, 238, 242);

const int BUTTON_HEIGHT = 25;
const int BUTTON_WIDTH = 100;
const int HEIGHT_REVAH = 25;
const int WIDTH_REVAH = 25;
/*
constructor of the board. build the border each iteration,
check the cordinate of the pressed buttons and draw the objects.
roll the board and everything in it

*/
Board::Board()

{
	// open the file
	std::ofstream myboard;
	myboard.open("board.txt");

	// variables
	bool saveCon = false;
	int genCount = 0;
	int robot_x = 0;
	int robot_y = 0;
	int lineCount = 0;
	double cellX = -1;
	double cellY = -1;
	int type = -1;

	// get number of rows and columns by function getSize
	int rows = getSize("rows");
	int cols = getSize("columns");

	// create the array that save the x,y and type of each painting
	double *genArr = new double[cols*cols * 2];

	if (rows > cols)
		double *genArr = new double[rows*rows*2];

	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Bomberman");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 40 && event.mouseButton.x <= 235) { // if selected from the menu
						type = checkMenu(event.mouseButton.y);
					}
					if (type == 7) {
						saveCon = true;
					}
					if ((event.mouseButton.x >= 275 && event.mouseButton.x <= 1255) && (type != -1)) { // if selected on board after selected from menu

						// find x,y of the pressed button
						cellY = checkRow(rows, event.mouseButton.y);
						cellX = checkCol(cols, event.mouseButton.x);

						// if the pressed button is for a wall, a rock, a door or a guard
						if (type == 0 || type == 2 || type == 3 || type == 4) {
							genArr[genCount] = cellX;
							genArr[genCount + 1] = cellY;
							genArr[genCount + 2] = type;
							genCount += 3;
						}
 
						// if the  pressed button is for a robot
						else if (type == 1) {
							robot_x = cellX;
							robot_y = cellY;
						}

						// if the pressed button is for delete
						if (type == 5) {
							for (int i = 0; i < genCount;i+=3) {
								if (genArr[i] == cellX && genArr[i + 1] == cellY) {
									genArr[i] = NULL;
									genArr[i + 1] = NULL;
									genArr[i + 2] = NULL;
									break;
								}
							}
						}
					}
					if (type == 6) { // if selected to clear board
						clearBoard(genArr, genCount);
						genCount = 0;
						robot_x = 0;
						robot_y = 0;
					}

				}			
			}
		}

		// clear the window with black color
		window.clear(sf::Color(142, 210, 201));

		// print the board and the menu
		printBoard(cols, rows, window);
		Menu menu(window);
		Button button(window);

		// print the selected objects on board
		if (saveCon) {
			save(myboard,genCount,cols,genArr);
			saveCon = false;
		}
		if(type > -1)
			Icons icon(40,520, type,window,195,165);
		if(robot_x > 0)
			Icons drawIcons(robot_x, robot_y, 1, window, 980.0 / cols, 670.0 / rows);
		if(genCount > 0)
			Icons drawIcon(genArr,window,cols,rows,genCount);

		// display the board and all objects each iteration
		window.display();	
	}
}


/*
get the size of the board from the user
*/
int Board::getSize(std::string sub)
{
	int temp;
	std::cout << "Enter number of " << sub << ": ";
	std::cin >> temp;
	return temp;
}


// print the board by rows and columns
void Board::printBoard(int rows, int cols, sf::RenderWindow& window)
{
	// print the painting board
	double cellWidth;
	double cellHeight;

	cellWidth = (1280.0 - (3 * WIDTH_REVAH) - 225) / rows;
	cellHeight = (670.0) / cols;

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
			cell.setFillColor(board_color);
			cell.setPosition(275 + (j*cellWidth), 25 + (i*cellHeight));
			cell.setOutlineThickness(1);
			cell.setOutlineColor(sf::Color(0, 170, 160));
			window.draw(cell);
		}
	}
	// ---- finish ----
}

/* check if the pressed button pressed on a menu button
   if yes - return it's number. if not - return -1
*/
int Board::checkMenu(double y)
{
	for (int i = 0; i < 8; i++) {
		if((y >= 40 + (i*60)) && (y <= 95 + (i*60)))
			return i;
	}
	return -1;
}

// return the line number for the y cordinate, -1 if none
double Board::checkRow(int rows, int y)
{
	int qurY = y;

	for (int i = 0; i < rows; i++) {
		if ((qurY >= 25 + (670.0 / rows)*i) && (qurY < 25 + (670.0 / rows)*(i + 1))) {
			return (25 + (670.0 / rows)*i);
		}
		
	}
	return -1;
}

// return the column number for the x cordinate, -1 if none
double Board::checkCol(int cols, int x)
{
	int qurX = x;

		for (int j = 0; j < cols; j++) {
			if ((qurX >= 275 + (980.0 / cols)*j) && ((qurX < 275 + (980.0 / cols)*(j + 1)))) {
				return (275 + (980.0 / cols)*j);
			}
		}
		return -1;
}

// clear the painting board from all objects
void Board::clearBoard(double * arr,int count)
{
	for (int i = 0; i < count; i++) {
		arr[i] = NULL;
	}
}

// write to file the board ("save")
void Board::save(std::ofstream &myboard, int genCount, int cols, double * genArr)
{
	int lineCount = 0;
	if (myboard.is_open()) {
		for (int key = 0; key < genCount; key += 3) {
			if (lineCount == cols) { // check for the end of the line
				myboard << endl;
				lineCount = 0;
			}
			if (int(genArr[key + 2]) == 0) {
				myboard << "#"; // wall
				lineCount++;
			}
			if (int(genArr[key + 2]) == 1) {
				myboard << "/"; // robot
				lineCount++;
			}
			if (int(genArr[key + 2]) == 2) {
				myboard << "!"; // guard
				lineCount++;
			}
			if (int(genArr[key + 2]) == 3) {
				myboard << "D"; // door
				lineCount++;
			}
			if (int(genArr[key + 2]) == 4) {
				myboard << "@"; // rock
				lineCount++;
			}

		}
	}
	myboard.close();
}




