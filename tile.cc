#include <iostream>
#include "tile.h"

const vector<vector<int>> TILES = {{0, 1, 3, 4, 8, 9}, {2, 3, 7, 8, 13, 14},
                                        {4, 5, 9, 10, 15, 16}, {6, 7, 12, 13, 18, 19},
                                        {8, 9, 14, 15, 20, 21}, {10, 11, 16, 17, 22, 23},
                                        {13, 14, 19, 20, 25, 26}, {15, 16, 21, 22, 27, 28},
                                        {18, 19, 24, 25, 30, 31}, {20, 21, 26, 27, 32, 33},
                                        {22, 23, 28, 29, 34, 35}, {25, 26, 31, 32, 37, 38},
                                        {27, 28, 33, 34, 39, 40}, {30, 31, 36, 37, 42, 43},
                                        {32, 33, 38, 39, 44, 45}, {34, 35, 40, 41, 46, 47},
                                        {37, 38, 43, 44, 48, 49}, {39, 40, 45, 46, 50, 51},
                                        {44, 45, 49, 50, 52, 53}};

const vector<vector<int>> R_and_C = {{0,3},{1,10},{3,5},{1,4},{-1,-1},{3,10},{2,11},{0,3},{3,8},{0,2},
    {0,6},{1,8},{4,12},{1,5},{4,11},{2,4},{4,6},{2,9},{2,9}};


Tile::Tile(int tile_index) : geese{false}, elements{TILES[tile_index]}, pos{tile_index},
 typeofResources{R_and_C[tile_index][0]}, chance{R_and_C[tile_index][1]} {};


string Tile::to_s() {
    if (typeofResources == 0) {
        return "  BRICK  ";
    } else if (typeofResources == 1) {
        return " ENERGY  ";
    } else if (typeofResources == 2) {
        return "  GLASS  ";
    } else if (typeofResources == 3) {
        return "  HEAT   ";
    } else if (typeofResources == 4) {
        return "  WIFI   ";
    } else {
        return "  PARK   ";
    }
}


string Tile::c_to_s() {
    if (chance == -1) {
        return "  ";
    }
    if (chance < 10) {
        return " " + to_string(chance);
    }
    return to_string(chance);
}


