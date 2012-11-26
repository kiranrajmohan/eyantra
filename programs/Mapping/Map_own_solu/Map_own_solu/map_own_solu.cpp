#include <iostream>
#include "Bot.h"

using namespace std;

const int arena[9][9]={
	{1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,0,0,1},
	{1,0,1,1,0,1,0,0,1},
	{1,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1}
};


void map(){

	/*at x,y
						check unmapped at y-1
								


				+---------->Move along x
				|				|
			mark open +---------+-----------+
				|	  |						|
				|	  V						V
				+--	no block			  block
											|
											V
										mark closed
											|
											V
										move to y+1
											|
											V
										  x==1    (no)--- move back on x---???
										  (yes)
											|
											V

	*/

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
	b.moveForwardAndCheck();
	b.printMap();

	b.turnRight();
	b.printMap();
	
	b.moveForwardAndCheck();
	b.printMap();





	map();
	b.printMap();

	cin.get();
	
}

