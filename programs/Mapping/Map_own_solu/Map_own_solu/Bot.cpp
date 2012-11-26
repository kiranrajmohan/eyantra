#include "Bot.h"

Bot::Bot()
{
	pos.a=pos.n=1;
	dir=North;
	for( int a=0;a<9;a++){
		for(int n=0;n<8;n++){
			map[a][n]=0;
		}
	}
	
	for( int a=0;a<9;a++){
		map[a][0]=map[a][8]=1;
	}
	for( int n=0;n<9;n++){
		map[0][n]=map[8][n]=1;
	}
	map[1][1]=MAP_OPEN;
	map[7][7]=MAP_OPEN;
}

void Bot::turnRight(){	if(dir==West) dir=North; else dir=Directions(dir+1);	} 
void Bot::turnLeft(){	if(dir==North) dir=West; else dir=Directions(dir-1);	}

bool Bot::moveForward(){
	XY xy=pos;
	switch(dir)
	{
	case North: xy.a++;
		break;
	case South: xy.a--;
		break;
	case East:  xy.n++;
		break;
	case West:  xy.n--;
		break;
	}
	if( map[xy.a][xy.n] == MAP_WALL){ //can't move, so return false
		return false;
	}else{
		pos=xy;
		return true;
	}
}

bool Bot::moveBack(){
	XY xy=pos;
	switch(dir)
	{
	case North: xy.a--;
		break;
	case South: xy.a++;
		break;
	case East:  xy.n--;
		break;
	case West:  xy.n++;
		break;
	}
	if( map[xy.a][xy.n] == MAP_WALL){ //can't move, so return false
		return false;
	}else{
		pos=xy;
		return true;
	}
}

void Bot::printDir(){
	switch(dir)
	{
	case North: cout<<"^ ";
		break;
	case South: cout<<"v ";
		break;
	case East:  cout<<"> ";
		break;
	case West:  cout<<"< ";
		break;
	}
}

XY Bot::getFront(){
	int a=pos.a,n=pos.n;
	switch(dir)
	{
	case North: return XY(a+1,n);
		break;
	case South: return XY(a-1,n);
		break;
	case East: return XY(a,n+1);
		break;
	case West: return XY(a,n-1);
		break;
	}
}
XY Bot::getBack(){
	int a=pos.a,n=pos.n;
	switch(dir)
	{
	case North: return XY(a-1,n);
		break;
	case South: return XY(a+1,n);
		break;
	case East: return XY(a,n-1);
		break;
	case West: return XY(a,n+1);
		break;
	}
}

XY Bot::getRight(){
	int a=pos.a,n=pos.n;
	switch(dir)
	{
	case North: return XY(a,n+1);
		break;
	case South: return XY(a,n-1);
		break;
	case East: return XY(a-1,n);
		break;
	case West: return XY(a+1,n);
		break;
	}
} 
XY Bot::getLeft(){
	int a=pos.a,n=pos.n;
	switch(dir)
	{
	case North: return XY(a,n-1);
		break;
	case South: return XY(a,n+1);
		break;
	case East: return XY(a+1,n);
		break;
	case West: return XY(a-1,n);
		break;
	}
}


bool Bot::checkFront(){
	XY p=getFront();
	if( arena[p.a][p.n] == ARENA_OPEN ){
		map[p.a][p.n]=MAP_OPEN;
		return true;
	}else{
		map[p.a][p.n]=MAP_WALL;
		return false;
	}
}

bool Bot::checkBack(){
	XY p=getBack();
	if( arena[p.a][p.n] == ARENA_OPEN ){
		map[p.a][p.n]=MAP_OPEN;
		return true;
	}else{
		map[p.a][p.n]=MAP_WALL;
		return false;
	}
}

bool Bot::checkLeft(){
	XY p=getLeft();
	if( arena[p.a][p.n] == ARENA_OPEN ){
		map[p.a][p.n]=MAP_OPEN;
		return true;
	}else{
		map[p.a][p.n]=MAP_WALL;
		return false;
	}
}

bool Bot::checkRight(){
	XY p=getRight();
	if( arena[p.a][p.n] == ARENA_OPEN ){
		map[p.a][p.n]=MAP_OPEN;
		return true;
	}else{
		map[p.a][p.n]=MAP_WALL;
		return false;
	}
}

void Bot::printMap()
{
	cout<<endl;
	cout<<"@"<<pos.a<<" "<<pos.n<<"facing";
	printDir();
	cout<<endl;
	for( int a=8;a>=0;a--){
		for(int n=0;n<9;n++){
			if( a==pos.a && n==pos.n){
				printDir();
			}else if( map[a][n] == UNMAPPED ){
				cout<<"* ";
			}else if( map[a][n] == MAP_WALL ){
				cout<<char(178)<<" ";
			}else{
				cout<<"  ";
			}
		}
		cout<<endl;
	}
	cin.get();
}

bool Bot::moveForwardAndCheck(){
	if( moveForward() == true ){
		checkFront();
		checkRight();
		checkLeft();
		return true;
	}else{
		return false;
	}
}

bool Bot::moveBackAndCheck(){
	if( moveBack() ==true ){
		checkFront();
		checkRight();
		checkLeft();
		return true;
	}else{
		return false;
	}
}