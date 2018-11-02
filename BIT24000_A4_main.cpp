/*
Assignment 4: Battleship
Written by Julianna Clarke - 101037898

This program replicates the game of Battleship, to be played against an AI or against another human
NOTE: to play against another human, no ships will be displayed to the board, so as to prevent cheating!

*/

#include <iostream>
#include <string>
#include "boat.h"
#include <Windows.h>
#include <time.h>
#include <vector>

using namespace std;

//function prototypes
void menu();
void drawBoard(int x, int y);
void gotoXY(int x, int y);
void placeShip(int x, int y, bool(&ships)[10][10], Boat* &boat, string(&sNames)[10][10]);
void drawShips(int x, int y, bool(&ships)[10][10]);
void createShips(vector <Boat*> &ships);
bool collision(int x, int y, bool(&ships)[10][10], vector <Boat*> &boatObjects, string(&sNames)[10][10]);
void clearLine(int x, int y);
bool allShipsSunk(bool(&ships)[10][10]);

//variable and array initialisations
const int boardSize = 10;

enum class States {
	Menu,
	SinglePlayer,
	MultiPlayer,
	Quit
};

int main() {

	States gamestate = States::Menu;
	int pChoice;

	vector <Boat*> p1Ships;
	vector <Boat*> p2Ships;

	bool p1ShipXY[10][10] = {{ 0 }};
	bool p2ShipXY[10][10] = {{ 0 }};

	string p1ShipNames[10][10] = { { "" } };
	string p2ShipNames[10][10] = { { "" } };

	bool p1Guessed[10][10] = { {0} };
	bool p2Guessed[10][10] = { { 0 } };

	const int board1X = 50;
	const int board1Y = 3;
	const int board2X = 50;
	const int board2Y = 19;

	const int writeX = 50;
	const int writeY = 15;
	int guessX, guessY;
	
	bool col;

	srand(time(NULL));

	while (true) {

		gotoXY(0, 0);
		if (gamestate == States::Menu) {
			menu();
			cin >> pChoice;

			switch (pChoice) {//switches game state depending on choice
			case 1:
				gamestate = States::SinglePlayer;
				break;
			case 2:
				gamestate = States::MultiPlayer;
				break;
			case 3:
				gamestate = States::Quit;
				break;
			}
		}
		else if (gamestate == States::SinglePlayer) {
			system("CLS");

			//create player one board and ships
			drawBoard(board1X, board1Y);
			createShips(p1Ships);

			for (int i = 0; i < 5; i++){
				placeShip(board1X, board1Y, p1ShipXY, p1Ships[i], p1ShipNames);
			}
			drawShips(board1X, board1Y, p1ShipXY); // ships only drawn for one player, only when user plays against AI

			//create player two board and ships
			drawBoard(board2X, board2Y);
			createShips(p2Ships);
			for (int i = 0; i < p2Ships.size(); i++) {
				placeShip(board2X, board2Y, p2ShipXY, p2Ships[i], p2ShipNames);
			}
			//system("PAUSE");

			bool gameOver = false; //	a nested infinite loop to handle just when the game is actually running, beyond setup
			while (!gameOver) {

				#pragma region player turn

				clearLine(writeX, writeY - 1);
				cout << "Player 1: \n";

				clearLine(writeX, writeY);
				cout << "Enter x value: ";
				cin >> guessX;

				clearLine(writeX, writeY);
				cout << "Enter y value: ";
				cin >> guessY;

				if (p1Guessed[guessX][guessY]) { // makes it an automatic miss if the player has already guessed the coordinate
					clearLine(writeX, writeY + 1);
					cout << "Miss!"; // but doesn't change any of the characters on screen
				}
				else {
					p1Guessed[guessX][guessY] = true;
					gotoXY(board1X - 35, board1Y);
					col = collision(guessX, guessY, p2ShipXY, p2Ships, p2ShipNames);

					if (col) {
						clearLine(writeX, writeY + 1);
						cout << "Hit!";
						gotoXY(guessX + board2X, guessY + board2Y);
						cout << (char)88;

						if (allShipsSunk(p2ShipXY)) {
							gameOver = true;
						}
					}
					else {
						clearLine(writeX, writeY + 1);
						cout << "Miss!";
						gotoXY(guessX + board2X, guessY + board2Y);
						cout << (char)61;
					}
					Sleep(1000);
				}
#pragma endregion

				#pragma region AI turn

				clearLine(writeX, writeY - 1);
				cout << "Computer: \n";

				guessX = rand() % 10;
				guessY = rand() % 10;

				if (p2Guessed[guessX][guessY]) {
					clearLine(writeX, writeY + 1);
					cout << "Miss!";
				}
				else {
					p2Guessed[guessX][guessY] = true;
					gotoXY(board2X - 35, board2Y);
					col = collision(guessX, guessY, p1ShipXY, p1Ships, p1ShipNames);

					if (col) {
						clearLine(writeX, writeY + 1);
						cout << "Computer Hit!";
						gotoXY(guessX + board1X, guessY + board1Y);
						cout << (char)88;

						if (allShipsSunk(p1ShipXY)) {
							gameOver = true;
						}
					}
					else {
						clearLine(writeX, writeY + 1);
						cout << "Computer Miss!";
						gotoXY(guessX + board1X, guessY + board1Y);
						cout << (char)61;
					}
					Sleep(500);
				}
#pragma endregion

				char playAgain;

				if (gameOver) {
					if (allShipsSunk(p2ShipXY)) {
						clearLine(writeX, writeY);
						cout << "Player 1 wins!";
						clearLine(writeX, writeY + 1);
						cout << "Would you like to play again? Y/N  ";
						cin >> playAgain;

					}
					else {
						clearLine(writeX, writeY);
						cout << "Player 2 wins!";
						clearLine(writeX, writeY + 1);
						cout << "Would you like to play again? Y/N  ";
						cin >> playAgain;
					}

					if (playAgain == 'n' || playAgain == 'N') {
						gamestate = States::Menu;
					}
				}
			}
		}

		else if (gamestate == States::MultiPlayer) {
			system("CLS");

			//create player one board and ships
			drawBoard(board1X, board1Y);
			createShips(p1Ships);
			for (int i = 0; i < p1Ships.size(); i++) {
				placeShip(board1X, board1Y, p1ShipXY, p1Ships[i], p1ShipNames);
			}

			//create player two board and ships
			drawBoard(board2X, board2Y);
			createShips(p2Ships);
			for (int i = 0; i < p2Ships.size(); i++) {
				placeShip(board2X, board2Y, p2ShipXY, p2Ships[i], p2ShipNames);
			}

			bool gameOver = false;
			while (!gameOver) {

				#pragma region p1 turn

				clearLine(writeX, writeY - 1);
				cout << "Player 1: \n";

				clearLine(writeX, writeY);
				cout << "Enter x value: ";
				cin >> guessX;

				clearLine(writeX, writeY);
				cout << "Enter y value: ";
				cin >> guessY;

				if (p1Guessed[guessX][guessY]) {
					clearLine(writeX, writeY + 1);
					cout << "Miss!";
				}
				else {
					p1Guessed[guessX][guessY] = true;
					gotoXY(board1X - 35, board1Y);
					col = collision(guessX, guessY, p2ShipXY, p2Ships, p2ShipNames);

					if (col) {
						clearLine(writeX, writeY + 1);
						cout << "Hit!";
						gotoXY(guessX + board2X, guessY + board2Y);
						cout << (char)88;

						if (allShipsSunk(p2ShipXY)) {
							gameOver = true;
						}
					}
					else {
						clearLine(writeX, writeY + 1);
						cout << "Miss!";
						gotoXY(guessX + board2X, guessY + board2Y);
						cout << (char)61;
					}
					Sleep(1000);
				}
				#pragma endregion

				#pragma region p2 turn

				clearLine(writeX, writeY - 1);
				cout << "Player 2: \n";

				clearLine(writeX, writeY);
				cout << "Enter x value: ";
				cin >> guessX;

				clearLine(writeX, writeY);
				cout << "Enter y value: ";
				cin >> guessY;

				if (p2Guessed[guessX][guessY]) {
					clearLine(writeX, writeY + 1);
					cout << "Miss!";
				}
				else {
					p2Guessed[guessX][guessY] = true;
					gotoXY(board2X - 35, board2Y);
					col = collision(guessX, guessY, p1ShipXY, p1Ships, p1ShipNames);

					if (col) {
						clearLine(writeX, writeY + 1);
						cout << "Hit!";
						gotoXY(guessX + board1X, guessY + board1Y);
						cout << (char)88;

						if (allShipsSunk(p1ShipXY)) {
							gameOver = true;
						}
					}
					else {
						clearLine(writeX, writeY + 1);
						cout << "Miss!";
						gotoXY(guessX + board1X, guessY + board1Y);
						cout << (char)61;
					}
					Sleep(1000);
				}
				#pragma endregion

				char playAgain;

				if (gameOver) {
					if (allShipsSunk(p2ShipXY)) {
						clearLine(writeX, writeY);
						cout << "Player 1 wins!";
						clearLine(writeX, writeY + 1);
						cout << "Would you like to play again? Y/N  ";
						cin >> playAgain;

					}
					else {
						clearLine(writeX, writeY);
						cout << "Player 2 wins!";
						clearLine(writeX, writeY + 1);
						cout << "Would you like to play again? Y/N  ";
						cin >> playAgain;
					}

					if (playAgain == 'n' || playAgain == 'N') {
						gamestate = States::Menu;
					}
				}
			}
		}

		else if (gamestate == States::Quit) {
			break;
		}
	}

	return 0;
}

void menu() {
	system("CLS");

	cout << "BATTLESHIP\n\n";
	cout << "1. Play Single Player Mode\n";
	cout << "2. Play Two Player Mode\n";
	cout << "3. Quit" << endl;
}

void gotoXY(int x, int y) {

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void createShips(vector <Boat*> &ships) {
	ships.clear();

	AircraftCarrier* ship1 = new AircraftCarrier;
	Battleship* ship2 = new Battleship;
	Submarine* ship3 = new Submarine;
	Cruiser* ship4 = new Cruiser;
	Destroyer* ship5 = new Destroyer;

	ships.push_back(ship1);
	ships.push_back(ship2);
	ships.push_back(ship3);
	ships.push_back(ship4);
	ships.push_back(ship5);
}

void drawBoard(int x, int y) { // draws just the board
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	gotoXY(x, y);

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout << (char)219;
		}
		gotoXY(x, y + i + 1);
	}
	gotoXY(x, y - 1);
	cout << "0123456789";
	for (int a = 0; a < boardSize; a++) {
		gotoXY(x - 1, y + a);
		cout << a;
	}
}

void placeShip(int x, int y, bool(&ships)[10][10], Boat* &boat, string(&sNames)[10][10]) {
	
	bool canPlace = false;
	bool newCoord = true; // for checking if a new coordinate is needed

	boat->setDirection(Direction::Up);

	while (newCoord) {

		newCoord = false;
		
		int randx = rand() % boardSize;
		int randy = rand() % boardSize;

		if (!(ships[randx][randy])) { // if there is no ship at the random coordinate
			while (!newCoord && !canPlace) {//while a new random coordinate is not needed, i.e. if all directions have not yet been checked

				switch (boat->getDirection()) {
				case Direction::Up:
					canPlace = true;

					for (int i = 0; i < (boat->getLength()); i++) {

						if ((randy + y - i) < y) {
							canPlace = false;
							boat->setDirection(Direction::Right);
							break;
						}
						else if ((ships[randx][randy - i])) {
							canPlace = false;
							boat->setDirection(Direction::Right);
							break;
						}
					}
					break;

				case Direction::Right:
					canPlace = true;

					for (int i = 0; i < boat->getLength(); i++) {
						if ((randx + x + i) > (x + boardSize)) {//if it exceeds the right limit
							canPlace = false;
							break;
						}
						else if ((ships[randx + i][randy])) {
							canPlace = false;
							break;
						}
					}
					if (!canPlace) {
						boat->setDirection(Direction::Down);
					}
					break;

				case Direction::Down:
					canPlace = true;

					for (int i = 0; i < boat->getLength(); i++) {
						if ((randy + y + i) > (y + boardSize)) {
							canPlace = false;
							break;
						}
						else if ((ships[randx][randy + i])) {
							canPlace = false;
							break;
						}
					}
					if (!canPlace) {
						boat->setDirection(Direction::Left);
					}
					break;

				case Direction::Left:
					canPlace = true;

					for (int i = 0; i < boat->getLength(); i++) {
						if ((randx + x - i) < x) {
							canPlace = false;
							newCoord = true;
							boat->setDirection(Direction::Up); //now if it can't be placed then it goes back to up and signals for a new coord
							break;
						}
						else if ((ships[randx - i][randy])) {
							canPlace = false;
							newCoord = true;
							boat->setDirection(Direction::Up);
							break;
						}
					}
					break;
				} // end of switch statement
			}
		}
		else {
			newCoord = true;
		}

		if (canPlace) { //actually place the dang ship, after a HEck ton of checks
			switch (boat->getDirection()) {
			case Direction::Up:
				for (int i = 0; i < boat->getLength(); i++) {
					ships[randx][randy - i] = true;
					sNames[randx][randy - i] = boat->getName();
				}
				boat->setXPosition(randx); // sets coordiates of the ship
				boat->setYPosition(randy);
				break;

			case Direction::Right:
				for (int i = 0; i < boat->getLength(); i++) {
					ships[randx + i][randy] = true;
					sNames[randx + i][randy] = boat->getName();
				}
				boat->setXPosition(randx);
				boat->setYPosition(randy);
				break;

			case Direction::Down:
				for (int i = 0; i < boat->getLength(); i++) {
					ships[randx][randy + i] = true;
					sNames[randx][randy + i] = boat->getName();
				}
				boat->setXPosition(randx);
				boat->setYPosition(randy);
				break;

			case Direction::Left:
				for (int i = 0; i < boat->getLength(); i++) {
					ships[randx - i][randy] = true;
					sNames[randx - i][randy] = boat->getName();
				}
				boat->setXPosition(randx);
				boat->setYPosition(randy);
				break;
			}
			newCoord = false;
		}

	}
}

void drawShips(int x, int y, bool(&ships)[10][10]) {

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (ships[i][j]) {
				gotoXY((x + i), (y + j));

				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 2);
				cout << (char)254; // HEY MAYBE CHANGE THE COLOUR OF THE BOATS
			}
		}
	}
}

bool collision(int x, int y, bool(&ships)[10][10], vector <Boat*> &boatObjects, string(&sNames)[10][10]) {

	int pastHits;
	if (ships[x][y]) {//if there is a ship at the coordinates
		for (int i = 0; i < boatObjects.size(); i++) {

			if (boatObjects[i]->getName() == sNames[x][y]) {
				pastHits = boatObjects[i]->getHits();
				boatObjects[i]->setHits(pastHits+1);

				if (boatObjects[i]->getHits() >= boatObjects[i]->getLength()) {
					boatObjects[i]->sunk();
				}
			}
		}
		ships[x][y] = false;	//removes the ship from the board so that it can not be hit again

		return true;
	}
	else {
		return false;
	}
}

void clearLine(int x, int y) {
	gotoXY(x, y);
	for (int i = 0; i < 30; i++) {
		cout << (char)255;
	}
	gotoXY(x, y);
}

bool allShipsSunk(bool(&ships)[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (ships[i][j]) {
				return false;
			}
		}
	}
	return true;
}
