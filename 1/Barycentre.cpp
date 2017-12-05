//~ Commande de Compilation : reset; g++ --std=c++14 -Wall -Wextra -o Barycentre Barycentre.cpp
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;
typedef struct Point Point;

Point createRandomPoint(bool ponderation = false);
void printPoint(const Point&);
void printPoint(const vector<Point>&);
vector<Point> createArrayPoint(unsigned int, bool ponderation = false);
float distance(Point const&, Point const&);
int closer(Point const&, vector<Point> const&);
Point barycentre(vector<Point> const&);

struct Point{
  float x;
  float y;
  float poids = 0.f;
};


int main(int argc, char **argv){
  srand(time(0));	
   	
  if(argc > 1){
    vector<Point> Arr = createArrayPoint(atoi(argv[1]), true);
    cout << "The barycenter point of the array of point: " << endl;
    printPoint(Arr);
			
  }

  vector<Point> Arr = createArrayPoint(5, true);
  cout << "The barycenter point of the array of point:\n ";
  printPoint(Arr);
  cout << "is the point:\n";
  printPoint(barycentre(Arr));
	
  return 0;
}

Point createRandomPoint(bool ponderation){
  float x = float(rand()) / float(RAND_MAX);
  float y = float(rand()) / float(RAND_MAX);
  float p = 0.f;
  if(ponderation){
    p = float(rand()) / float(RAND_MAX);
  }
  return {x, y, p};
}

vector<Point> createArrayPoint(unsigned int n, bool ponderation){
  vector<Point> arr;
	
  for(unsigned int i = 0; i < n; i++)
    arr.push_back(createRandomPoint(ponderation));
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
	     << p.y << endl
	     << p.poids << endl << endl;
}

void printPoint(const vector<Point> &arr){
	
	for(auto a : arr){
		cout << a.x << endl
		     << a.y << endl
		     << a.poids << endl << endl;
	}
}

Point barycentre(const vector<Point> &arr){

  float acc = 0.f;
  float xacc = 0.f;
  float yacc = 0.f;
  for(Point p : arr){
    xacc += p.poids * p.x;
    yacc += p.poids * p.y;
    acc += p.poids;
  }

  if(acc != 0.f){
    xacc /= acc;
    yacc /= acc;
  }
  
  return {xacc, yacc, 1.f};
}
