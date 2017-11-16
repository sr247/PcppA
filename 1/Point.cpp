//~ Commande de Compilation : reset; g++ --std=c++14 -Wall -Wextra -o 
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
typedef struct Point Point;

Point createRandomPoint();
void printPoint(const Point&);


struct Point{
	float x;
	float y;
};


int main(int argc, char **argv){
	srand(time(0));	
   	
	Point p = createRandomPoint();
	printPoint(p);
	
	return 0;
}

Point createRandomPoint(){
	float x = float(rand()) / float(RAND_MAX);
	float y = float(rand()) / float(RAND_MAX);
	return {x, y};
}

void printPoint(const Point &p){
	
	cout << p.x << endl
		 << p.y << endl;
}

