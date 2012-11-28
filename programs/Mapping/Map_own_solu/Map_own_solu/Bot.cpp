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
	map[1][1]=MAP_VISITED;
	map[7][7]=MAP_OPEN;
}

void Bot::turnRight(){	if(dir==West) dir=North; else dir=Directions(dir+1);	} 
void Bot::turnLeft(){	if(dir==North) dir=West; else dir=Directions(dir-1);	}

void Bot::turnToTrueDir(){
	if( (pos.n%2)==1 ){ //odd=>north
		switch(dir)
		{
		case South: 
			turnRight();
			turnRight();
			break;
		case East:  
			turnLeft();
			break;
		case West: 
			turnRight();
			break;
		}
	}else{
		switch(dir)
		{
		case North: 
			turnRight();
			turnRight();
			break;
		case East:  
			turnRight();
			break;
		case West: 
			turnLeft();
			break;
		}
	}
}
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
		map[xy.a][xy.n]=MAP_VISITED;
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
		map[xy.a][xy.n]=MAP_VISITED;
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
	if( map[p.a][p.n] == MAP_WALL ){
		return false;
	}else if( map[p.a][p.n] == MAP_OPEN || map[p.a][p.n] == MAP_VISITED ){
		return true;
	}

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
	if( map[p.a][p.n] == MAP_WALL ){
		return false;
	}else if( map[p.a][p.n] == MAP_OPEN || map[p.a][p.n] == MAP_VISITED ){
		return true;
	}

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
	if( map[p.a][p.n] == MAP_WALL ){
		return false;
	}else if( map[p.a][p.n] == MAP_OPEN || map[p.a][p.n] == MAP_VISITED ){
		return true;
	}

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
	
	if( map[p.a][p.n] == MAP_WALL ){
		return false;
	}else if( map[p.a][p.n] == MAP_OPEN || map[p.a][p.n] == MAP_VISITED ){
		return true;
	}

	if( arena[p.a][p.n] == ARENA_OPEN ){
		map[p.a][p.n]=MAP_OPEN;
		return true;
	}else{
		map[p.a][p.n]=MAP_WALL;
		return false;
	}
}

bool Bot::isFrontVisited(){
	XY p=getFront();
	if( map[p.a][p.n]==MAP_VISITED){
		return true;
	}else{
		return false;
	}
}

bool Bot::isBackVisited(){
	XY p=getBack();
	if( map[p.a][p.n]==MAP_VISITED){
		return true;
	}else{
		return false;
	}
}

bool Bot::isLeftVisited(){
	XY p=getLeft();
	if( map[p.a][p.n]==MAP_VISITED){
		return true;
	}else{
		return false;
	}
}

bool Bot::isRightVisited(){
	XY p=getRight();
	if( map[p.a][p.n]==MAP_VISITED){
		return true;
	}else{
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
			}else if( map[a][n] == MAP_OPEN ){
				cout<<"  ";
			}else{
				cout<<char(250)<<" ";
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

bool Bot::checkNextLine(){
	if( dir == North ){
		return checkRight();
	}else if( dir== South ){
		return checkLeft();
	}else if( dir== West){
		return checkBack();
	}else{
		return checkFront();
	}
}

bool Bot::checkPrevLine(){
	if( dir == South ){
		return checkRight();
	}else if( dir== North ){
		return checkLeft();
	}else if( dir== East){
		return checkBack();
	}else{
		return checkFront();
	}
}

bool Bot::goToNextLine(){
	if( checkNextLine() ){
		if( dir == West ) turnRight();

		if( dir == North ) turnRight();
		else if( dir== South ) turnLeft();

		moveForward();
		return true;
	}else{
		return false;
	}
}

bool Bot::goToPrevLine(){
	if( checkPrevLine() ){
		if( dir == West ) turnLeft();

		if( dir == North ) turnLeft();
		else if( dir== South ) turnRight();

		moveForward();
		return true;
	}else{
		return false;
	}
}
/*
void Bot::blockLine(){
	int a=1,n=1;
	for(n=1;n<7;n++){
		for(a=1;a<8;a++){
			if( map[a][n] == MAP_OPEN ||  map[a][n] == UNMAPPED ){
				return;
			}
		} //full line mapped
		for(a=1;a<8;a++){
			if( map[a][n+1] == MAP_OPEN ||  map[a][n+1] == UNMAPPED ){
				return;
			}
		} //full line mapped
		for(a=1;a<9;a++){
			map[a][n] = MAP_WALL;
		}
	}
}
*/
bool Bot::isSuccess(){

	for( int a=1;a<9;a++){
		for(int n=1;n<9;n++){
			if( map[a][n] == UNMAPPED || map[a][n] == MAP_OPEN ){
				cout<<"\nFAILURE! unsuccessful mapping! :( "<<endl;
				return false;
			}
		}
	}
	cout<<"\nCongrats! successfully mapped\n";
	return true;

}