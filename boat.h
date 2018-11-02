/*
Assignment 4: Battleship
Written by Julianna Clarke

This is the header file to define the class boat, and it's derived classes
*/

#include <iostream>
#include <string>
using namespace std;

enum class Direction {
	Up,
	Right,
	Down,
	Left
};

class Boat {

public:
	int m_length;
	string m_name;
	int m_x_position;
	int m_y_position;
	int m_hits;
	Direction m_direction;

	virtual void sunk() = 0;
	int getLength();
	int getXPosition();
	int getYPosition();
	string getName();
	Direction getDirection();
	int getHits();

	void setDirection(Direction d);
	void setXPosition(int x);
	void setYPosition(int y);
	void setHits(int hits);
};

class AircraftCarrier : public Boat {
public:
	AircraftCarrier() { m_length = 5; m_name = "airCarrier"; m_hits = 0; }
	virtual void sunk();

};

class Battleship : public Boat {
public:
	Battleship() { m_length = 4; m_name = "battle"; m_hits = 0; }
	virtual void sunk();

};

class Submarine : public Boat {
public:
	Submarine() { m_length = 3; m_name = "sub"; m_hits = 0; }
	virtual void sunk();

};

class Cruiser : public Boat {
public:
	Cruiser() { m_length = 3; m_name = "cruise"; m_hits = 0; }
	virtual void sunk();

};

class Destroyer : public Boat {
public:
	Destroyer() { m_length = 2; m_name = "dest"; m_hits = 0; }
	virtual void sunk();

};
