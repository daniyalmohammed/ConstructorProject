#ifndef BOARD_H
#define BOARD_H
#include <fstream>
#include <sstream>
#include "tile.h"
#include "builder.h"
#include "vertices.h"
#include "edges.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
using namespace std;

class Board {
	public:
	string loadout;
    default_random_engine rng;
    int curTurn;
    int goose_location;
    vector<Tile> tiles;
    vector<Builder> builders;
	vector<Edge> roads;
	vector<Vertex> vertices;
	const string colours[4] = {"Blue","Red","Orange","Yellow"};
	const string types[6] = {"BRICK","ENERGY","GLASS","HEAT","WIFI","PARK"};
	int dice_modes[4];
	void init(); 
	void loadFile(string file_name); 
	void save(string file_name); 
	void seed(string input);
	bool trade(string color, string give, string take); 
	void status(); 
	void printBoard(); 
	void helpCommandsPrint(); 
	void next(); 
	bool canBuild(int vertex_index); 
	void build(int vertex_index); 
	bool canImprove(int vertex_index); 
	void improve(int vertex_index); 
	void distribution(int n); 
	void SevenRolled(); 
	bool rollDice(); 
	bool loadedDice(); 
	bool fairDice(); 
	bool canBuildRoad(int road_index); 
	void buildRoad(int road_index); 
	bool canFirst8(int vertex_index); 
	bool first8(); 
	bool moveGeese(); 
	int colour_to_index(string colour); 
	int material_to_index(string material); 
	string GeeseStr(int index); 
	void testTile(); 
	void stealResource(int steal_from); 
	void getRez(); 
	void loadBoard(string file_name); 
	void randomBoard(); 
	bool checkWin(); 
};
#endif

