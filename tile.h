#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>
using namespace std;

class Tile {
    bool geese;
    int elements[6];
    int pos;
    int typeofResources;
    // int resources;
    // int chance;
    void tilesInitialization(int tile_index);
};

#endif
