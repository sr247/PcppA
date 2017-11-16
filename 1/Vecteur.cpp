//~ Commande de Compilation : reset; g++ --std=c++14 -Wall -Wextra -o Vecteur Vecteur.cpp
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;
typedef struct Point Point;

Point createRandomPoint();
void printPoint(const Point&);
void printPoint(const vector<Point>&);
vector<Point> createArrayPoint(unsigned int);

struct Point{
	float x;
	float y;
};


int main(int argc, char **argv){
	srand(time(0));	
   	
   	if(argc > 1){
		vector<Point> Arr = createArrayPoint(atoi(argv[1]));
		printPoint(Arr);
	}
	
	
	return 0;
}

Point createRandomPoint(){
	float x = float(rand()) / float(RAND_MAX);
	float y = float(rand()) / float(RAND_MAX);
	return {x, y};
}


vector<Point> createArrayPoint(unsigned int n){
	vector<Point> arr;
	
	for(unsigned int i = 0; i < n; i++)
		arr.push_back(createRandomPoint());
	return arr;
}

void printPoint(const Point &p){
	
	cout << p.x << endl
		 << p.y << endl;
}

void printPoint(const vector<Point> &arr){
	
	for(auto a : arr){
		cout << a.x << endl
			<< a.y << endl << endl;
	}
}
