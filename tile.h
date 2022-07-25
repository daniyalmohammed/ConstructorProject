#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>
using namespace std;

class Tile {
    public:
        bool geese;
        vector<int> elements;
        int pos;
        int typeofResources;
        int chance;
        Tile(int tile_index);
        string to_s();
        string c_to_s();
};

#endif
