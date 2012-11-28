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

vector<XY> Bot::Astar(XY dest){

	enum cellCostEnum{
		frontCost=0,
		leftCost,
		rightCost,
		backCost
	};
	int cellCost[]={10,15,15,20}; //min cost for forward since moving forward is fastest

	struct cell{
		XY pos;
		cell *parent;

		cell( XY _pos ){ pos=_pos; parent=NULL }
		cell( XY _pos,cell *_par){ pos=_pos; parent=_par; }
		int cost,heu,total;

		void calCost(int c){
			if( parent == NULL ){ //first cell
				cost=0;
				return;
			}
			cost= parent->cost + c;
		}

		void calHeu(XY dest){
			int a=pos.a-dest.a;
			int n=pos.n-dest.n;
			if( a<0 ) a*=-1;
			if( n<0 ) n*=-1;
			heu = 10*(a+n);
		}

		void cal(int c,XY dest){
			calCost(c);
			calHeu(dest);
			total=cost+heu;
		}
	};

	vector<cell> open,closed;

	cell parent(pos);
	parent.cal(0, dest);
	open.push_back( parent ); //push in first starting point

	while( !(pos.a==dest.a && pos.n==dest.n) ){

		if( checkFront(pos.a,pos.n) ){
			cell ce= cell( getFront( pos.a,pos.n) , &parent ) ;
			ce.cal( cellCost[frontCost], dest );
			open.push_back( ce ); //push in any cell that is open or visited.
		}

		if( checkRight(pos.a,pos.n) ){
			cell ce= cell( getRight( pos.a,pos.n) , &parent ) ;
			ce.cal( cellCost[ rightCost], dest );
			open.push_back( ce ); //push in any cell that is open or visited.
		}

		if( checkLeft(pos.a,pos.n) ){
			cell ce= cell( getLeft( pos.a,pos.n) , &parent ) ;
			ce.cal( cellCost[leftCost], dest );
			open.push_back( ce ); //push in any cell that is open or visited.
		}

		if( checkBack(pos.a,pos.n) ){
			cell ce= cell( getBack( pos.a,pos.n) , &parent ) ;
			ce.cal( cellCost[backCost] , dest );
			open.push_back( ce ); //push in any cell that is open or visited.
		}

		closed.push_back( parent );
		open.pop_back();

		cell minCell=open.begin();
		for(vector<cell> ::iterator  it=open.begin(); it!=open.end(); ++it){
			if( it->total < minCell.total){
				minCell= *it;
			}
		}


	}
}

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

