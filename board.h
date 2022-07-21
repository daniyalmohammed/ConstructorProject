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
#include "TextDisplay.h"
#include <memory>
using namespace std;

class Board {
	unique_ptr<TextDisplay> td = nullptr;
    default_random_engine rng;
    bool win;
    // int curTure;
    int goose_location;
    vector<Tile> tiles;
    vector<Builder> builders;
	vector<Edge> roads;
	vector<Vertex> vertices;
	// string colours[4] = {"Blue","Red","Orange","Yellow"};
	// string initials[4] = {"B","R","O","Y"};
	// string types[6] = {"BRICK","ENERGY","GLASS","HEAT","WIFI","PARK"};
	// int dice_modes[4];
	// bool loadedGame = false;
	void init();
	~Board();
	void loadFile(string file_name);
	void loadBoard(string file_name);
	vector<int> seed(string input);
	void randomBoard();
	void trade(int color, int give, int take);	
	void status();
	// std::string convert(int num);
	// std::string trans(std::string str);
	// void printBoard();
	void residences();
	// void printHelp();
	// void next();
	// void save(string file_name);
	// bool canBuild(int vertex_index);
	// void build(int vertex_index);
	// void improve(int vertex_index);
	void distribution(int n);
	void rollDice();
	void loadedDice();
	void fairDice();
	void buildRoad(int road_index);
	void first8();
	void moveGeese(int index);
	int colour_to_index(string colour);
	private:
		void testTile();
};
#endif




