#pragma once
#include <iostream>
#include <vector> 
using namespace std;

#define UNMAPPED	0
#define MAP_WALL	1
#define MAP_OPEN	2
#define MAP_VISITED 3

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

	void turnToTrueDir();
	
	void printDir();

	XY getFront(int a,int n);
	XY getBack(int a,int n);
	XY getLeft(int a,int n);
	XY getRight(int a,int n); 

	XY getFront();
	XY getBack();
	XY getLeft();
	XY getRight(); 

	bool checkFront(int a,int n);
	bool checkBack(int a,int n);
	bool checkLeft(int a,int n);
	bool checkRight(int a,int n);

	bool checkFront();
	bool checkBack();
	bool checkLeft();
	bool checkRight();

	bool isFrontVisited();
	bool isBackVisited();
	bool isLeftVisited();
	bool isRightVisited();

	bool checkNextLine();
	bool checkPrevLine();

	bool moveForwardAndCheck();
	bool moveBackAndCheck();

	bool goToNextLine();
	bool goToPrevLine();

	void printMap();

	bool isSuccess();

	//void blockLine();

	vector<XY> Astar(XY dest);
	void run();
	
};
