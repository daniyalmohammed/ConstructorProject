#ifndef VERTICES_H
#define VERTICES_H
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
using namespace std;

class Vertex {
	public:
		int pos;
		int residenceLevel;	//0 nothing, 1 basement, 2 house, 3 tower
		int owner_index;
		vector<int> neighbor;
		vector<int> my_roads;
		Vertex(int location);
		void upgrade();
		void notify();
		void colonize(int builder_index);
		string getIn();
};
#endif
