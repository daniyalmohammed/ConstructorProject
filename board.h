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
    default_random_engine rng;
    bool win;
    int curTurn;
    int goose_location;
    vector<Tile> tiles;
    vector<Builder> builders;
	vector<Edge> roads;
	vector<Vertex> vertices;
	const string colours[4] = {"Blue","Red","Orange","Yellow"};
	// string initials[4] = {"B","R","O","Y"};
	const string types[6] = {"BRICK","ENERGY","GLASS","HEAT","WIFI","PARK"};
	int dice_modes[4];
	// bool loadedGame = false;
	void init(); // done
	void loadFile(string file_name); // Gio
	void save(string file_name); // Done
	void seed(string input);
	// void randomBoard();
	void trade(string color, string give, string take); // Dani -- done
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
	void distribution(int n); // Done
	void SevenRolled(); // Dani -- done
	void rollDice(); // H -- done
	void loadedDice(); // H -- done
	void fairDice(); // H -- done
	bool canBuildRoad(int road_index); // Dani -- done
	void buildRoad(int road_index); // Dani -- done
	bool canFirst8(int vertex_index); // Done
	void first8(); // H -- done
	void moveGeese(); // Dani
	int colour_to_index(string colour); // done
	int material_to_index(string material); // Dani done
	string GeeseStr(int index); // Done
	void testTile(); // H -- done
	void stealResource(int steal_from); // Dani -- done
	void getRez(); // done
	void loadBoard(string file_name); // gio
	void randomBoard(); // gio
	bool checkWin(); // dani done
	void saveGame(string file_name); // gio save game to file file_name
};
#endif
