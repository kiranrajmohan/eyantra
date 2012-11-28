#include <iostream>
#include "Bot.h"

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
	{1,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,1},
	{1,0,1,0,0,1,0,0,1},
	{1,0,0,1,0,0,1,0,1},
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

	botStatus stat=stat_forward;
	//Directions savedDir=dir;
	int origLine=1;

	while(1) //!(pos.a==7 && pos.n==7)  )
	{
		switch( stat ){
		case stat_forward:
			cout<<"forward "<<lineDir( pos.n );
		//	if( lineDir( pos.n )==Bot::North ){
				if( (pos.a==7 && lineDir(pos.n)==North) || (pos.a==1 && lineDir(pos.n)==South) ){
					stat=stat_endOfLine;
				}else if( checkFront() ){
					if(isFrontVisited()){
						if( !goToNextLine() ){
							stat=stat_followWall;
						}
					}else{
						moveForwardAndCheck();
					}
				}else{ //front blocked
					stat=stat_followWall;
					origLine=pos.n;
				}
			//}
			break;
		case stat_endOfLine: 
			cout<<"endOfline";
			if( goToNextLine() ){
				if( lineDir(pos.n)==North ){
					turnLeft();
				}else{
					turnRight();
				}
				stat=stat_forward;
			}else{
				stat=stat_followWall;
			}
			break;

		case stat_followWall: 
			//TODO stick to wall
			//if( lineDir(origLine)==North ){
				cout<<" leftist ";
				if( checkLeft() && !isLeftVisited() ){ 
					cout<<" left ";
					turnLeft();
					moveForwardAndCheck();
				}else if( checkFront() && !isFrontVisited() ){
					cout<<" front ";
					moveForwardAndCheck();
				}else if( checkRight() && ! isRightVisited() ){
					cout<<" Right ";
					turnRight();
					moveForwardAndCheck();
				}else if( checkLeft()  ){ 
					cout<<" left ";
					turnLeft();
					moveForwardAndCheck();
				}else if( checkFront() ){
					cout<<" front ";
					moveForwardAndCheck();
				}else if( checkRight() ){
					cout<<" Right ";
					turnRight();
					moveForwardAndCheck();
				}else{
					cout<<"\nDEADEND!\n";
					turnRight();
					turnRight();
					moveForward();
				}
			//}

			if( pos.n==origLine && dir==lineDir(origLine) ){
				stat=stat_forward;
			}
			break;
		default:
			cout<<"No Default!";
		}
		//blockLine();
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

