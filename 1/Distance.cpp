//~ Commande de Compilation : reset; g++ --std=c++14 -Wall -Wextra -o Distance Distance.cpp
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
float distance(Point const&, Point const&);
int closer(Point const&, vector<Point> const&);

struct Point{
	float x;
	float y;
};


int main(int argc, char **argv){
	srand(time(0));	
   	
   	if(argc > 1){
		vector<Point> Arr = createArrayPoint(atoi(argv[1]));
		printPoint(Arr);
		
		int c = closer({1.f,1.f}, Arr);
		cout << "The point {1.f,1.f} is closer to the point of id " << c 
		<< " in Arr" << endl;
			
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


float distance(Point const &p1, Point const &p2){
	
	return sqrt(pow(p2.x-p1.x, 2) + pow(p2.y - p1.y, 2));
}



int closer(Point const& p, vector<Point> const& Arr){
	float min = distance(p, Arr[0]);
	int id = 0;
	for(unsigned int i = 1; i < Arr.size(); i++){ 
		float tmp = distance(p, Arr[i]);
		if(tmp < min){
			id = i;
			min = tmp;
		} 
	}
	return id;
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
