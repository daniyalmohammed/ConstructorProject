#ifndef VERTICES_H
#define VERTICES_H
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
using namespace std;

class Vertex : public Subject {
	int pos;
	int residenceLevel;	
	int owner_index;
	vector<int> neighbor;
	vector<int> my_roads;
	Vertex(int location);
	void upgrade();
	void notify();
	void colonize(int builder_index);
	string getVertexInfo();
};
#endif
