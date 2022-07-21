#ifndef EDGES_H
#define EDGES_H

#include <vector>
#include <string>
#include "subject.h"
using namespace std;

class Edge {
    int pos;
    int owner_index;
    vector<int> neighborVertex;
    vector<int> neighborEdges;
    Edge(int location);
    void colonize(int builder_index);
    void notify();
    string getEdgeInfo();
};

#endif
