#include <iostream>
#include "Bot.h"
#include <vector>

using namespace std;

const int arena1[9][9]={
	{1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,1},
	{1,1,1,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,1},
	{1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1}
};

const int arena[9][9]={
	{1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,1,0,1},
	{1,1,1,0,1,0,0,0,1},
	{1,0,1,0,1,1,0,0,1},
	{1,0,1,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1}
};


Bot::Directions lineDir(int l){
	return ( (l%2)? Bot::North : Bot::South ); 
}

enum botStatus
{
	stat_forward=0,
	stat_endOfLine,
	stat_followWall,
};

void Bot::run()
{
	/*
	keep track of last unvisited 
	preference to right
	try to keep going straight as long as possible
	*/
	bool recheckUnvisited=false;
	vector<XY> lastUnvisited;
	while(1) 
	{
		cout<<"("<<pos.a<<" "<<pos.n<<")\n";
		if( checkFront() && !isFrontVisited() ){
			moveForward();
			recheckUnvisited=true;
		}else if( checkLeft() && !isLeftVisited() ){
			turnLeft();
		}else if( checkRight() && !isRightVisited() ){
			turnRight();
		}else if(checkFront()){
			moveForward();	
			recheckUnvisited=true;
		}else{
			turnRight();
		}

		if( recheckUnvisited){
			for(vector<XY> ::reverse_iterator  it=lastUnvisited.rbegin(); it!=lastUnvisited.rend(); ++it){
				if( it->a==pos.a && it->n==pos.n){
					lastUnvisited.erase((it+1).base());
					break;
				}
			}
			if( checkRight() && !isRightVisited()){ lastUnvisited.push_back( getRight() ); }
			if( checkLeft() && !isLeftVisited()){ lastUnvisited.push_back( getLeft() ); }
			recheckUnvisited=false;
		}
		cout<<"lastUnVisited =>";
		for(vector<XY> ::iterator it=lastUnvisited.begin(); it!=lastUnvisited.end(); ++it){
			cout<<" ("<<it->a<<","<<it->n<<") ";
		}
		cout<<endl;
		printMap();
	}
}

void main()
{
	/*
	mapArray[i][j]
	y\x ->
	|		0	1	2	3	4	5	6	7	8
	V	 +-----------------------------------
		0|	1	1	1	1	1	1	1	1	1
		1|	1	0	0	0	0	0	0	0	1
		2|	1	0	0	0	0	0	0	0	1
		3|	1	0	0	0	0	0	0	0	1
		4|	1	0	0	0	0	0	0	0	1
		5|	1	0	0	0	0	0	0	0	1
		6|	1	0	0	0	0	0	0	0	1
		7|	1	0	0	0	0	0	0	0	1
		8|	1	1	1	1	1	1	1	1	1
	*/
	/*
		0	-> unmapped
		1	-> wall
		2	-> open
	*/

	//make mapArray
	Bot b;

	b.printMap();
	//b.moveForwardAndCheck();

	b.run();
	b.isSuccess();
	b.printMap();

	cin.get();
	
}

