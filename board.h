#ifndef BOARD_H
#define BOARD_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "tile.h"
#include "builder.h"
#include "vertex.h"

using namespace std;

class Board {
    default_random_engine rng;
    bool win;
    int curTure;
    int goose_location
    vector<Tile> tiles;
    vector<Builder> builders;
		vector<string> roads;
		vector<Vertex> vertices;
		string colours[4] = {"Blue","Red","Orange","Yellow"};
		string initials[4] = {"B","R","O","Y"};
		string types[6] = {"BRICK","ENERGY","GLASS","HEAT","WIFI","PARK"};
		int dice_modes[4];
		bool loadedGame = false;
		void init();
		~Board();
		void loadFile(string file_name);
		void loadBoard(string file_name);
		std::vector<int> seed(string input);
		void randomBoard();
		void trade(int builder2, int give, int take);	
		void status();
		std::string convert(int num);
		std::string trans(std::string str);
		void printBoard();
		void residence();
		void printHelp();
		void next();
		void save(string file_name);
		bool canBuild(int vertex_index);
		void build(int vertex_index);
		void improve(int vertex_index);
		void distribute(int num);
		void roll();
		void loadedDice();
		void fairDice();
		void buildRoad(int road_index);
		void first8();
		void moveGeese();
		int colour_to_index(string colour);
	private:
		void testTile();
};
#endif




}