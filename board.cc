#include "board.h"
#include <vector>
#include "tile.h"
#include "builder.h"
#include "vertices.h"
#include "edges.h"
#include <memory>
#include <string>
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

bool Board::canBuild(int vertex_index, int player) {
    if (vertices[vertex_index].owner_index != -1) {
        return false;
    }
    for(auto ind_1: vertices[vertex_index].neighbor) {
        if (vertices[ind_1].owner_index != -1) {
            return false;
        }
    }
    for(auto ind_2: vertices[vertex_index].my_roads) {
        if (roads[ind_2].owner_index == player) {
            return true;
        }
    }
    return false;
}

void Board::build(int vertex_index, int player) {
    vertices[vertex_index].colonize(player);
}

bool Board::canBuildRoad(int road_index, int player) {
    if (roads[road_index].owner_index != -1) {
        return false;
    }
    for(auto ind_1 : roads[road_index].neighborVertex) {
        if (vertices[ind_1].owner_index == player) {
            return true;
        }
    }
    for (std::size_t i = 0; i < roads[road_index].neighborEdges.size(); ++i) {
        if (roads[roads[road_index].neighborEdges[i]].owner_index == player) {
            if ( vertices[roads[road_index].neighborVertex[i]].owner_index == -1) {
                return true;
            }
        }
    }
    return false;
}


void Board::buildRoad(int road_index, int player) {
    roads[road_index].colonize(player);
}

int Board::colour_to_index(string colour) {
    if (colour == "B" || colour == "Blue") {
        return 0;
    }
    if (colour == "R" || colour == "Red") {
        return 1;
    }
    if (colour == "O" || colour == "Orange") {
        return 2;
    }
    return 3;
}




