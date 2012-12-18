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

struct mapCell;

struct XY{
	XY(){}
	XY(int _a,int _n){ a=_a; n=_n; }
	int a,n; //alphabet & the number
};

extern const int arena[9][9];
struct Acell;

struct mapCell
{
	XY pos;
	bool	isInOpen,
			isInClosed;
	Acell* AstarCell;
	int type;

	mapCell(){
		isInOpen=isInClosed=false;
		type=UNMAPPED;
	}
};

class Bot
{
	mapCell map[9][9];
public:
	Bot();
	Bot( const Bot &b);
	enum Directions{
		North=0,
		East,
		South,
		West
	};

	mapCell *cellOnMap;
	Directions dir;

	mapCell* getMapCell( XY xy);
	bool moveForward();
	bool moveBack();
	void turnLeft();
	void turnRight(); 

	void turnToTrueDir();

	void turnNorth();
	void turnSouth(); 
	void turnEast();
	void turnWest(); 
	
	void printDir();

	mapCell* getFront(int a,int n);
	mapCell* getBack(int a,int n);
	mapCell* getLeft(int a,int n);
	mapCell* getRight(int a,int n); 

	mapCell* getFront();
	mapCell* getBack();
	mapCell* getLeft();
	mapCell* getRight(); 

	Directions getLeftDir();
	Directions getRightDir(); 
	Directions getBackDir();

	bool check( mapCell* mC);
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

	//vector<mapCell*> Astar(mapCell* destCell);
	void run();
	
};
