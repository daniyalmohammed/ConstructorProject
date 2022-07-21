#include "board.h"
#include <vector>
#include "tile.h"
#include "builder.h"
#include "vertices.h"
#include "edges.h"
#include <memory>
using namespace std;

void Board::init() {
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
}


