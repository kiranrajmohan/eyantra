#pragma once
#include <iostream>
using namespace std;

#define UNMAPPED	0
#define MAP_WALL	1
#define MAP_OPEN	2

#define ARENA_OPEN	0
#define ARENA_WALL	1

struct XY{
	XY(){}
	XY(int _a,int _n){ a=_a; n=_n; }

	int a,n; //alphabet & the number
};

extern const int arena[9][9];

class Bot
{
	int map[9][9];
public:
	Bot();
	enum Directions{
		North=0,
		East,
		South,
		West

	};

	XY pos;
	Directions dir;

	bool moveForward();
	bool moveBack();
	void turnLeft();
	void turnRight(); 
	

	void printDir();

	XY getFront();
	XY getBack();
	XY getLeft();
	XY getRight(); 

	bool checkFront();
	bool checkBack();
	bool checkLeft();
	bool checkRight(); 

	bool moveForwardAndCheck();
	bool moveBackAndCheck();

	void printMap();
	
};
