/*
Assignment 4: Battleship
Written by Julianna Clarke

This is the file that defines the methods for the classes in boat.h

*/

#include "boat.h"
#include<iostream>
using namespace std;


#pragma region Getters
int Boat::getLength() {
	return (m_length);
 }

int Boat::getXPosition() {
	return(m_x_position);
}

int Boat::getYPosition() {
	return (m_y_position);
}

Direction Boat::getDirection() {
	return (m_direction);
}

string Boat::getName() {
	return (m_name);
}

int Boat::getHits() { 
	return(m_hits); 
}
#pragma endregion

#pragma region Setters
void Boat::setDirection(Direction d) {
	m_direction = d;
}

void Boat::setXPosition(int x) {
	m_x_position = x;
}

void Boat::setYPosition(int y) {
	m_y_position = y;
}

void Boat::setHits(int hits) {
	m_hits = hits;
}
#pragma endregion

#pragma region Sunk methods
void AircraftCarrier::sunk() {
	cout << "You sunk the Aircraft Carrier!";
}

void Battleship::sunk() {
	cout << "You sunk the Battleship!";
}

void Submarine::sunk() {
	cout << "You sunk the Submarine!";
}

void Cruiser::sunk() {
	cout << "You sunk the Cruiser!";
}

void Destroyer::sunk() {
	cout << "You sunk the Destroyer!";
}
#pragma endregion

