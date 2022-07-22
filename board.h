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
	// string types[6] = {"BRICK","ENERGY","GLASS","HEAT","WIFI","PARK"};
	int dice_modes[4];
	// bool loadedGame = false;
	void init(); //somewhat done
	void loadFile(string file_name); // Gio
	void save(string file_name); // Gio
	// vector<int> seed(string input);
	// void randomBoard();
	void trade(int color, int give, int take); // Dani
	void status(); // Dani
	// std::string convert(int num);
	// std::string trans(std::string str);
	void printBoard(); // Gio
	void residences(); // H
	void printHelp(); // Dani
	void next(); // H
	bool canBuild(int vertex_index, int player); //done but need to add material check
	void build(int vertex_index, int player); //done remove material 
	bool canImprove(int vertex_index, int player); // Gio, Dani do material
	void improve(int vertex_index, int player); // Gio, Dani do material
	void distribution(int n); // Gio 
	void SevenRolled(); // Dani
	void rollDice(); // H
	void loadedDice(); // H
	void fairDice(); // H
	bool canBuildRoad(int road_index, int player); // Dani do material
	void buildRoad(int road_index, int player); // Dani do material
	bool canFirst8(int vertex_index, int player); // Gio
	void first8(); // H
	void moveGeese(int index); // done
	int colour_to_index(string colour); // done
	private:
		void testTile();
};
#endif




