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
    default_random_engine rng;
    bool win;
    int curTurn;
    int goose_location;
    vector<Tile> tiles;
    vector<Builder> builders;
	vector<Edge> roads;
	vector<Vertex> vertices;
	string colours[4] = {"Blue","Red","Orange","Yellow"};
	// string initials[4] = {"B","R","O","Y"};
	string types[6] = {"BRICK","ENERGY","GLASS","HEAT","WIFI","PARK"};
	int dice_modes[4];
	// bool loadedGame = false;
	void init(); //somewhat done
	void loadFile(string file_name); // Gio
	void save(string file_name); // Gio
	// vector<int> seed(string input);
	// void randomBoard();
	void trade(int color, int give, int take); // Dani -- done
	void status(); // Dani - done
	// std::string convert(int num);
	// std::string trans(std::string str);
	void printBoard(); // Done
	void residences(); // H -- done
	void helpCommandsPrint(); // Dani -- done
	void next(); // H -- done
	bool canBuild(int vertex_index); //Dani -- done
	void build(int vertex_index); //Dani -- done
	bool canImprove(int vertex_index); // Dani -- material done
	void improve(int vertex_index); // Dani -- material done
	void distribution(int n); // Gio 
	void SevenRolled(); // Dani -- done
	void rollDice(); // H -- done
	void loadedDice(); // H -- done
	void fairDice(); // H -- done
	bool canBuildRoad(int road_index); // Dani -- done
	void buildRoad(int road_index); // Dani -- done
	bool canFirst8(int vertex_index); // Done
	void first8(); // H
	void moveGeese(); // Dani
	int colour_to_index(string colour); // done
	string GeeseStr(int index); // Done
	void testTile(); // H -- done
};
#endif




