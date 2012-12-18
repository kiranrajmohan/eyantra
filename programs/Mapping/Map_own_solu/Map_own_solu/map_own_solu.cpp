#include <iostream>
#include "Bot.h"
#include <list>
#include <stack>

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

list<mapCell*> Astar1(Bot b,mapCell* destCell){

	enum cellCostEnum{
		frontCost=0,
		leftCost,
		rightCost,
		backCost
	};

	XY dest=destCell->pos;

	struct cell{
		mapCell *cellOnMap;
		cell *parent;
		XY pos; //for ease of use
		cellCostEnum cellDir;
		int cost,heu,total;

		void calCost(cellCostEnum c){
			int cellCost[]={10,15,15,20}; //min cost for forward since moving forward is fastest
			if( parent == NULL ){ //first cell
				cost=0;
				return;
			}
			cost= parent->cost + cellCost[c];
		}

		void calHeu(XY dest){
			int a=cellOnMap->pos.a - dest.a;
			int n=cellOnMap->pos.n - dest.n;
			if( a<0 ) a*=-1;
			if( n<0 ) n*=-1;
			heu = 10*(a+n);
		}

		cell( mapCell *_cellOnMap ,mapCell* dest,cellCostEnum dir ){ 
			cellOnMap=_cellOnMap;
			parent=NULL; 
			pos=cellOnMap->pos; 
			cellDir=dir;

			calCost(dir);
			calHeu(dest->pos);
			total=cost+heu;
		}

		cell( mapCell *_cellOnMap, mapCell* dest, cell* _parent ,cellCostEnum dir){ 
			cellOnMap=_cellOnMap; 
			parent=_parent; 
			pos=cellOnMap->pos;
			cellDir=dir;

			calCost(dir);
			calHeu(dest->pos);
			total=cost+heu;
		}

		cell(const cell &c){
			cellOnMap=c.cellOnMap;
			parent=c.parent;
			pos=c.pos; //for ease of use
			cellDir=c.cellDir;
			cost=c.cost;
			heu=c.heu;
			total=c.total;
		}
		cell(){

		}

		bool operator==(const cell &c){
			if( c.pos.a==pos.a && c.pos.n==pos.n ){
				return true;
			}else{
				return false;
			}
		}
		

	};

	list<cell> open,closed;

	cell c(b.cellOnMap,destCell,frontCost);
	open.push_back( c ); //push in first starting point
	c.cellOnMap->isInOpen=true;

	while( !(c.pos.a==dest.a && c.pos.n==dest.n) ){

		mapCell* tempMC = b.getFront( c.pos.a,c.pos.n) ;
		if(  !tempMC->isInClosed && !tempMC->isInOpen && b.check(tempMC) ){
			open.push_back( cell( tempMC ,destCell, &c, frontCost ) ); //push in any cell that is open or visited.
			tempMC->isInOpen=true;
		}

		tempMC = b.getRight( c.pos.a,c.pos.n) ;
		if(  !tempMC->isInClosed && !tempMC->isInOpen && b.check(tempMC) ){
			open.push_back( cell( tempMC ,destCell, &c, rightCost ) ); //push in any cell that is open or visited.
			tempMC->isInOpen=true;
		}

		tempMC = b.getLeft( c.pos.a,c.pos.n) ;
		if(  !tempMC->isInClosed && !tempMC->isInOpen && b.check(tempMC) ){
			open.push_back( cell( tempMC ,destCell, &c, leftCost ) ); //push in any cell that is open or visited.
			tempMC->isInOpen=true;
		}

		tempMC = b.getBack( c.pos.a,c.pos.n) ;
		if(  !tempMC->isInClosed && !tempMC->isInOpen && b.check(tempMC) ){
			open.push_back( cell ( tempMC ,destCell, &c, backCost ) ); //push in any cell that is open or visited.
			tempMC->isInOpen=true;
		}


		closed.push_back( c );
		open.remove( c );
		c.cellOnMap->isInClosed=true;
		c.cellOnMap->isInOpen=false;

		list<cell>::iterator minCell=open.begin();
		for(list<cell>::iterator  it=open.begin(); it!=open.end(); ++it){
			if( it->total < minCell->total){
				minCell= it;
			}
		}

		cout<<"\nopen =>";
		for(list<cell> ::iterator it=open.begin(); it!=open.end(); ++it){
			cout<<" ("<<it->pos.a<<","<<it->pos.n<<") ";
		}

		cout<<"\nClosed =>";
		for(list<cell> ::iterator it=closed.begin(); it!=closed.end(); ++it){
			cout<<" ("<<it->pos.a<<","<<it->pos.n<<") ";
		}

		c=*minCell;
		closed.push_back( *minCell );
		open.erase( minCell );
		c.cellOnMap->isInClosed=true;
		c.cellOnMap->isInOpen=false;
		
	}

	return list<mapCell*>() ;
}

struct Acell
{
	mapCell* mC;
	Acell* parent;
	int G, H, F; //cost,heu,total
	Bot::Directions dir;

	Acell( mapCell* _mC , Acell* &_parent, int cellCost, mapCell* destCell ){
		mC=_mC;
		parent=_parent;
		mC->AstarCell=this;

		if( parent!=NULL){
			cout<<"\ndefault ("<<mC->pos.a<<" "<<mC->pos.n<<") has parent ("<<parent->mC->pos.a<<" "<<parent->mC->pos.n<<") ";
		}

		calG( cellCost );
		calH( destCell );
		calF();
		dir=Bot::North;
	}

	Acell( const Acell &a ){
		mC=a.mC;
		parent=a.parent;
		mC->AstarCell=this;

		if( parent!=NULL){
			cout<<"\ncopy ("<<mC->pos.a<<" "<<mC->pos.n<<") has parent ("<<parent->mC->pos.a<<" "<<parent->mC->pos.n<<") ";
		}

		G=a.G;
		H=a.H;
		F=a.F;
		dir=a.dir;
		
	}

	void calG(int _cellCost ){
		if( parent!=NULL){
			G= parent->G + _cellCost;
		}else{
			G=0;
		}
	}

	void calH( mapCell* destCell ){
		int a=mC->pos.a - destCell->pos.a;
		int n=mC->pos.n - destCell->pos.n;
		if( a<0 ) a*=-1;
		if( n<0 ) n*=-1;
		H = 10*(a+n);
	}

	void calF(){
		F = G+H;
	}

	void updateVal(int _cellCost){
		calG(_cellCost);
		calF();
	}
	void setDir(Bot::Directions d){
		dir=d;
	}
};

void updateOpen(Bot &b,Acell &c, list<Acell> &open, mapCell* destCell){

		mapCell* tempCell = b.getFront( b.cellOnMap->pos.a, b.cellOnMap->pos.n );
		Acell tempAcell( tempCell, &c, 10, destCell );

		if( !tempCell->isInOpen ){
			if( !tempCell->isInClosed && b.check( tempCell) ){
				tempCell->isInOpen=true;
				tempAcell.setDir( b.dir );
				cout<<"cell in front pushed "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				open.push_back( tempAcell ); 
			}
		}else{
			if( tempAcell.G < c.G ){
				c.parent=&tempAcell;
				cout<<"parent updated front "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				c.updateVal(10); //what should be the cost?????
			}
		}

		tempCell = b.getRight( );
		tempAcell=Acell( tempCell, &c, 15, destCell );
		if( !tempCell->isInOpen ){
			if( !tempCell->isInClosed && b.check( tempCell) ){
				tempCell->isInOpen=true;
				tempAcell.setDir( b.getRightDir() );
				cout<<"cell in right pushed "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				open.push_back( tempAcell ); 
			}
		}else{
			if( tempAcell.G < c.G ){
				c.parent=&tempAcell;
				cout<<"parent updated right "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				c.updateVal(15); //what should be the cost?????
			}
		}

		tempCell = b.getLeft(  );
		tempAcell=Acell( tempCell, &c, 15, destCell );
		if( !tempCell->isInOpen ){
			if( !tempCell->isInClosed && b.check( tempCell) ){
				tempCell->isInOpen=true;
				tempAcell.setDir( b.getLeftDir() );
				cout<<"cell in left pushed "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				open.push_back( tempAcell ); 
			}
		}else{
			if( tempAcell.G < c.G ){
				c.parent=&tempAcell;
				cout<<"parent updated left "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				c.updateVal(15); //what should be the cost?????
			}
		}

		tempCell = b.getBack( );
		tempAcell=Acell( tempCell, &c, 20, destCell );
		if( !tempCell->isInOpen ){
			if( !tempCell->isInClosed && b.check( tempCell) ){
				tempCell->isInOpen=true;
				tempAcell.setDir( b.getBackDir() );
				cout<<"cell in back pushed "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				open.push_back( tempAcell ); 
			}
		}else{
			if( tempAcell.G < c.G ){
				c.parent=&tempAcell;
				cout<<"parent updated back "<<tempCell->pos.a<<" "<<tempCell->pos.n<<" "<<tempAcell.dir<<"\n";
				c.updateVal(20); //what should be the cost?????
			}
		}

}
//list<mapCell*> Astar(Bot b, mapCell* destCell){
void Astar(Bot b, mapCell* destCell){

	cout<<"\n----------------- A* -------------------------\n";
	XY start=b.cellOnMap->pos;
	XY dest = destCell->pos;
	destCell=b.getMapCell(dest); //translate the mapCell of the original Bot to that of the AStar Bot

	list<Acell> open,closed;
	Acell c( b.cellOnMap, NULL,0 , destCell );
	c.setDir( b.dir );

	b.cellOnMap->AstarCell = &c;
	b.cellOnMap->isInOpen=true;
	open.push_back( c );


	while( 1 )
	{
		cin.get();

		switch( c.dir ){
		case Bot::North:
			b.turnNorth();
			break;
		case Bot::South:
			b.turnSouth();
			break;
		case Bot::East:
			b.turnEast();
			break;
		case Bot::West:
			b.turnWest();
			break;
		}
		b.moveForward();
		cout<<endl<<b.cellOnMap->pos.a<<" "<<b.cellOnMap->pos.n<<" "<<c.mC->pos.a<<" "<<c.mC->pos.n<<"\n";
		b.printDir();
		cout<<endl;
		b.printMap();
		if(dest.a == b.cellOnMap->pos.a && dest.n ==b.cellOnMap->pos.n ){
			if( destCell->AstarCell->parent!=NULL ){
				break;
			}
		}

		updateOpen(b,c,open,destCell);

		cout<<"\nopen =>";
		for(list<Acell> ::iterator it=open.begin(); it!=open.end(); ++it){
			cout<<" ("<<it->mC->pos.a<<","<<it->mC->pos.n<<" "<<it->F<<")";
			if( it->parent!=NULL ){
				cout<<"=>("<<it->parent->mC->pos.a<<","<<it->parent->mC->pos.n<<") ";
			}else{
				cout<<"=>NULL ";
			}
		}

		cout<<"\nClosed =>";
		for(list<Acell> ::iterator it=closed.begin(); it!=closed.end(); ++it){
			cout<<" ("<<it->mC->pos.a<<","<<it->mC->pos.n<<" "<<it->F<<")";
			if( it->parent!=NULL ){
				cout<<"=>("<<it->parent->mC->pos.a<<","<<it->parent->mC->pos.n<<") ";
			}else{
				cout<<"=>NULL ";
			}
		}

		list<Acell>::iterator minCell=open.begin();
		for(list<Acell>::iterator  it=open.begin(); it!=open.end(); ++it){
			if( it->F < minCell->F ){
				minCell= it;
			}
		}

		cout<<"\n minCell="<<minCell->mC->pos.a<<" "<<minCell->mC->pos.n<<" "<<minCell->dir<<"\n";
		closed.push_back( *minCell );
		c=closed.back();
		c.mC->isInClosed=true;
		c.mC->isInOpen=false;
		if(open.empty()){
			break;
		}else{
			open.erase( minCell );
		}
		

		cout<<"\nopen =>";
		for(list<Acell> ::iterator it=open.begin(); it!=open.end(); ++it){
			cout<<" ("<<it->mC->pos.a<<","<<it->mC->pos.n<<" "<<it->F<<")";
			if( it->parent!=NULL ){
				cout<<"=>("<<it->parent->mC->pos.a<<","<<it->parent->mC->pos.n<<") ";
			}else{
				cout<<"=>NULL ";
			}
		}

		cout<<"\nClosed =>";
		for(list<Acell> ::iterator it=closed.begin(); it!=closed.end(); ++it){
			cout<<" ("<<it->mC->pos.a<<","<<it->mC->pos.n<<" "<<it->F<<")";
			if( it->parent!=NULL ){
				cout<<"=>("<<it->parent->mC->pos.a<<","<<it->parent->mC->pos.n<<") ";
			}else{
				cout<<"=>NULL ";
			}
		}

		
		cout<<"\n########################################################\n";
		
	}

	list<mapCell*> path;
	Acell* temp=&closed.back();
	while( temp->parent!=NULL ){
		path.push_back( temp->mC );
		temp= temp->parent;
	}

	cout<<"\npath =>";
	for(list<mapCell*>::iterator it=path.begin(); it!=path.end(); ++it){
		cout<<" ("<<(*it)->pos.a<<","<<(*it)->pos.n<<") ";
	}

	cin.get();

}

void Bot::run()
{
	/*
	keep track of last unvisited 
	preference to right
	try to keep going straight as long as possible
	*/
	bool recheckUnvisited=false;
	list<mapCell*> lastUnvisited;
	while(1) 
	{
		cout<<"("<<cellOnMap->pos.a<<" "<<cellOnMap->pos.n<<")\n";
		if( checkFront() && !isFrontVisited() ){
			moveForward();
			recheckUnvisited=true;
		}else if( checkLeft() && !isLeftVisited() ){
			turnLeft();
		}else if( checkRight() && !isRightVisited() ){
			turnRight();
		}
		//else if(checkFront()){
//			moveForward();	
			//recheckUnvisited=true;
//		}
		else{
			//turnRight();
			Astar(*this, lastUnvisited.back() );
		}

		if( recheckUnvisited){
			for(list<mapCell*>::iterator  it=lastUnvisited.begin(); it!=lastUnvisited.end(); ++it){ //better with reverse itereator since the cell moved to will be among the last added
				if( (*it)->pos.a==cellOnMap->pos.a && (*it)->pos.n==cellOnMap->pos.n){
					//lastUnvisited.erase( (it+1).base() );
					lastUnvisited.erase( it );
					break;
				}
			}
			if( checkRight() && !isRightVisited()){ lastUnvisited.push_back( getRight() ); }
			if( checkLeft() && !isLeftVisited()){ lastUnvisited.push_back( getLeft() ); }
			recheckUnvisited=false;
		}
		cout<<"lastUnVisited =>";
		for(list<mapCell*> ::iterator it=lastUnvisited.begin(); it!=lastUnvisited.end(); ++it){
			cout<<" ("<<(*it)->pos.a<<","<<(*it)->pos.n<<") ";
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

