#ifndef EDGES_H
#define EDGES_H
#include <vector>
#include <string>
using namespace std;

class Edge {
    public:
        int pos;
        int owner_index;
        vector<int> neighborVertex;
        vector<int> neighborEdges;
        Edge(int location);
        void colonize(int builder_index);
        void notify();
        string getIn();
};

#endif


