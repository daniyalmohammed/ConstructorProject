#include "vertices.h"
#include <vector>
#include <string>

const vector<vector<int>> all_roads = {{0,1},{0,2},
	{3,5},{1,3,6},{2,4,7},{4,8},
	{9,12},{5,9,13},{6,10,14},{7,10,15},{8,11,16},{11,17},
	{12,20},{13,18,21},{14,18,22},{15,19,23},{16,19,24},{17,25},
	{20,26,29},{21,26,30},{22,27,31},{23,27,32},{24,28,33},{25,28,34},
	{29,37},{30,35,38},{31,35,39},{32,36,40},{33,36,41},{34,42},
	{37,43,46},{38,43,47},{39,44,48},{40,44,49},{41,45,50},{42,45,51},
	{46,54},{47,52,55},{48,52,56},{49,53,57},{50,53,58},{51,59},
	{54,60},{55,60,63},{56,61,64},{57,61,65},{58,62,66},{59,62},
	{63,67},{64,67,69},{65,68,79},{66,68},
	{69,71},{70,71}};

const vector<vector<int>> collectNeighbours = {{1,3},{0,4},
    {3,7},{0,2,8},{1,5,9},{4,10},
	{7,12},{2,6,13},{3,9,14},{4,8,15},{5,11,16},{10,17},
	{6,18},{7,14,19},{8,13,20},{9,16,21},{10,15,22},{11,23},
	{12,19,24},{13,18,25},{14,21,26},{15,20,27},{16,23,28},{17,22,29},
	{18,30},{19,26,31},{20,25,32},{21,28,33},{22,27,34},{23,35},
	{24,31,36},{25,30,37},{26,33,38},{27,32,39},{28,35,40},{29,34,41},
	{30,42},{31,38,34},{32,37,44},{33,40,45},{34,39,46},{35,47},
	{36,43},{37,42,48},{38,45,49},{39,44,50},{40,47,51},{41,46},
	{43,49},{44,48,52},{45,51,53},{46,50},
	{49,53},{50,52}};

const string res_types[4] = {" ","B","H","T"};
const string builders[4] = {"B","R","O","Y"};

Vertex::Vertex(int location) : pos{location}, residenceLevel{0},
 owner_index{-1}, neighbor{collectNeighbours[location]},
 my_roads{all_roads[location]} {};

void Vertex::colonize(int builder_index) {
    residenceLevel = 1;
    owner_index = builder_index;
}

void Vertex::upgrade() {
    residenceLevel += 1;
}

string Vertex::getVertexInfo() {
    if (owner_index == -1) {
        return "  ";
    } else {
        return builders[owner_index] + res_types[residenceLevel];
    }
}
