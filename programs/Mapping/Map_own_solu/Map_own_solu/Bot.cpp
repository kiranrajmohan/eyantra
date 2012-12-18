#include "Bot.h"

Bot::Bot()
{
	cellOnMap=&map[1][1];
	dir=North;
	for( int a=0;a<9;a++){
		for(int n=0;n<8;n++){
			map[a][n].pos.a=a;
			map[a][n].pos.n=n;
		}
	}
	for( int a=0;a<9;a++){
		map[a][0].type=map[a][8].type=MAP_WALL;
	}
	for( int n=0;n<9;n++){
		map[0][n].type=map[8][n].type=MAP_WALL;
	}
	map[1][1].type=MAP_VISITED;
	map[7][7].type=MAP_OPEN;
}

Bot::Bot( const Bot &b){
	for( int i=0;i<9; i++){
		for( int j=0;j<9;j++){
			map[i][j]=b.map[i][j];
		}
	}
	
	cellOnMap=&map[b.cellOnMap->pos.a][b.cellOnMap->pos.n];
	dir=b.dir;
}

mapCell* Bot::getMapCell( XY xy)
{
	return &map[xy.a][xy.n];
}

void Bot::turnRight(){	if(dir==West) dir=North; else dir=Directions(dir+1);	} 
void Bot::turnLeft(){	if(dir==North) dir=West; else dir=Directions(dir-1);	}

Bot::Directions Bot::getLeftDir(){
	if(dir==North) return West; else return Directions(dir-1);
}

Bot::Directions Bot::getRightDir(){
	if(dir==West) return North; else return Directions(dir+1);
}

Bot::Directions Bot::getBackDir(){
	if(dir==South) return North; 
	else if( dir==West ) return East;
	else return Directions(dir+2);
}

void Bot::turnNorth(){
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
}

void Bot::turnSouth(){
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

void Bot::turnEast(){
	switch(dir)
	{
	case West: 
		turnRight();
		turnRight();
		break;
	case North:  
		turnRight();
		break;
	case South: 
		turnLeft();
		break;
	}
}

void Bot::turnWest(){
	switch(dir)
	{
	case East: 
		turnRight();
		turnRight();
		break;
	case South:  
		turnRight();
		break;
	case North: 
		turnLeft();
		break;
	}
}



void Bot::turnToTrueDir(){
	if( (cellOnMap->pos.n%2)==1 ){ //odd=>north
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
	XY xy=cellOnMap->pos;
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
	if( map[xy.a][xy.n].type == MAP_WALL){ //can't move, so return false
		return false;
	}else{
		cellOnMap->pos=xy;
		map[xy.a][xy.n].type=MAP_VISITED;
		return true;
	}
}

bool Bot::moveBack(){
	XY xy=cellOnMap->pos;
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
	if( map[xy.a][xy.n].type == MAP_WALL){ //can't move, so return false
		return false;
	}else{
		cellOnMap->pos=xy;
		map[xy.a][xy.n].type=MAP_VISITED;
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

mapCell* Bot::getFront(int a,int n){
	switch(dir)
	{
	case North: return &map[a+1][n];
		break;
	case South: return &map[a-1][n];
		break;
	case East: return &map[a][n+1];
		break;
	case West: return &map[a][n-1];
		break;
	}
}
mapCell* Bot::getBack(int a,int n){
	switch(dir)
	{
	case North: return &map[a-1][n];
		break;
	case South: return &map[a+1][n];
		break;
	case East: return &map[a][n-1];
		break;
	case West: return &map[a][n+1];
		break;
	}
}

mapCell* Bot::getRight(int a,int n){
	switch(dir)
	{
	case North: return &map[a][n+1];
		break;
	case South: return &map[a][n-1];
		break;
	case East: return &map[a-1][n];
		break;
	case West: return &map[a+1][n];
		break;
	}
} 
mapCell* Bot::getLeft(int a,int n){
	switch(dir)
	{
	case North: return &map[a][n-1];
		break;
	case South: return &map[a][n+1];
		break;
	case East: return &map[a+1][n];
		break;
	case West: return &map[a-1][n];
		break;
	}
}

mapCell* Bot::getFront(){
	return getFront( cellOnMap->pos.a,cellOnMap->pos.n);
}
mapCell* Bot::getBack(){
	return getBack( cellOnMap->pos.a,cellOnMap->pos.n);
}

mapCell* Bot::getRight(){
	return getRight( cellOnMap->pos.a,cellOnMap->pos.n);
} 
mapCell* Bot::getLeft(){
	return getLeft( cellOnMap->pos.a,cellOnMap->pos.n);
}

bool Bot::check( mapCell* mC){

	if( mC->type == MAP_WALL ){
		return false;
	}else if( mC->type == MAP_OPEN || mC->type == MAP_VISITED ){
		return true;
	}

	if( arena[mC->pos.a][mC->pos.n] == ARENA_OPEN ){
		mC->type=MAP_OPEN;
		return true;
	}else{
		mC->type=MAP_WALL;
		return false;
	}

}


bool Bot::checkFront(int a,int n){
	mapCell* p=getFront();
	if( map[p->pos.a][p->pos.n].type == MAP_WALL ){
		return false;
	}else if( map[p->pos.a][p->pos.n].type == MAP_OPEN || map[p->pos.a][p->pos.n].type == MAP_VISITED ){
		return true;
	}

	if( arena[p->pos.a][p->pos.n] == ARENA_OPEN ){
		map[p->pos.a][p->pos.n].type=MAP_OPEN;
		return true;
	}else{
		map[p->pos.a][p->pos.n].type=MAP_WALL;
		return false;
	}
}

bool Bot::checkBack(int a,int n){
	mapCell* p=getBack();
	if( map[p->pos.a][p->pos.n].type == MAP_WALL ){
		return false;
	}else if( map[p->pos.a][p->pos.n].type == MAP_OPEN || map[p->pos.a][p->pos.n].type == MAP_VISITED ){
		return true;
	}

	if( arena[p->pos.a][p->pos.n] == ARENA_OPEN ){
		map[p->pos.a][p->pos.n].type=MAP_OPEN;
		return true;
	}else{
		map[p->pos.a][p->pos.n].type=MAP_WALL;
		return false;
	}
}

bool Bot::checkLeft(int a,int n){
	mapCell* p=getLeft();	
	if( map[p->pos.a][p->pos.n].type == MAP_WALL ){
		return false;
	}else if( map[p->pos.a][p->pos.n].type == MAP_OPEN || map[p->pos.a][p->pos.n].type == MAP_VISITED ){
		return true;
	}

	if( arena[p->pos.a][p->pos.n]== ARENA_OPEN ){
		map[p->pos.a][p->pos.n].type=MAP_OPEN;
		return true;
	}else{
		map[p->pos.a][p->pos.n].type =MAP_WALL;
		return false;
	}
}

bool Bot::checkRight(int a,int n){
	mapCell* p=getRight();
	
	if( map[p->pos.a][p->pos.n].type == MAP_WALL ){
		return false;
	}else if( map[p->pos.a][p->pos.n].type == MAP_OPEN || map[p->pos.a][p->pos.n].type == MAP_VISITED ){
		return true;
	}

	if( arena[p->pos.a][p->pos.n] == ARENA_OPEN ){
		map[p->pos.a][p->pos.n].type =MAP_OPEN;
		return true;
	}else{
		map[p->pos.a][p->pos.n].type =MAP_WALL;
		return false;
	}
}

bool Bot::checkFront(){
	return checkFront( cellOnMap->pos.a , cellOnMap->pos.n );
}

bool Bot::checkBack(){
	return checkBack( cellOnMap->pos.a , cellOnMap->pos.n );
}

bool Bot::checkLeft(){
	return checkLeft( cellOnMap->pos.a , cellOnMap->pos.n );
}

bool Bot::checkRight(){
	return checkRight( cellOnMap->pos.a , cellOnMap->pos.n );
}

bool Bot::isFrontVisited(){
	mapCell* p=getFront();
	if( map[p->pos.a][p->pos.n].type == MAP_VISITED){
		return true;
	}else{
		return false;
	}
}

bool Bot::isBackVisited(){
	mapCell* p=getBack();
	if( map[p->pos.a][p->pos.n].type ==MAP_VISITED){
		return true;
	}else{
		return false;
	}
}

bool Bot::isLeftVisited(){
	mapCell* p=getLeft();
	if( map[p->pos.a][p->pos.n].type ==MAP_VISITED){
		return true;
	}else{
		return false;
	}
}

bool Bot::isRightVisited(){
	mapCell* p=getRight();
	if( map[p->pos.a][p->pos.n].type ==MAP_VISITED){
		return true;
	}else{
		return false;
	}
}
void Bot::printMap()
{
	cout<<endl;
	cout<<"@"<<cellOnMap->pos.a<<" "<<cellOnMap->pos.n<<"facing";
	printDir();
	cout<<endl;
	for( int a=8;a>=0;a--){
		for(int n=0;n<9;n++){
			if( a==cellOnMap->pos.a && n==cellOnMap->pos.n){
				printDir();
			}else if( map[a][n].type == UNMAPPED ){
				cout<<"* ";
			}else if( map[a][n].type == MAP_WALL ){
				cout<<char(178)<<" ";
			}else if( map[a][n].type == MAP_OPEN ){
				cout<<"  ";
			}else{
				cout<<char(250)<<" ";
			}
		}
		cout<<endl;
	}
	//cin.get();
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
			if( map[a][n].type == UNMAPPED || map[a][n].type == MAP_OPEN ){
				cout<<"\nFAILURE! unsuccessful mapping! :( "<<endl;
				return false;
			}
		}
	}
	cout<<"\nCongrats! successfully mapped\n";
	return true;

}