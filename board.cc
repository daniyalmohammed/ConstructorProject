#include "board.h"
#include <vector>
#include "tile.h"
#include "builder.h"
#include "vertices.h"
#include "edges.h"
#include <memory>
using namespace std;

void Board::init() {
    curTurn = 0;
    td = make_unique<TextDisplay>();
    win = false;
    tiles.resize(19);
    for (int t = 0; t < 19; ++t) {
        tilesInitialization(tiles[t]);
    }
    tiles[4].geese = true;
    goose_location = 4;
    roads.resize(72);
    for (int r = 0; r < 72; ++r) {
        (roads[r]) = Edge{r};
    }
    vertices.resize(54);
    for (int v = 0; v < 54; ++v) {
        (vertices[v]) = Vertex{v};
    }
    builders.resize(4);
    for (int b = 0; b < 4; ++b) {
        (builders[b]) = Builder{b};
    }
}

void Board::moveGeese(int index) {
    tiles[goose_location].geese = false;
    tiles[index].geese = true;
    goose_location = index;
}

bool Board::canBuild(int vertex_index) {
    if (vertices[vertex_index].owner_index != -1) {
        return false;
    }
    for(auto ind_1: vertices[vertex_index].neighbor) {
        if (vertices[ind_1].owner_index != -1) {
            return false;
        }
    }
    for(auto ind_2: vertices[vertex_index].my_roads) {

    }
}

