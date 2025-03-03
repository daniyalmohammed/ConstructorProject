#include "edges.h"
#include <vector>
#include <string>
using namespace std;

const vector<vector<int>> edge_neighbors = {{1, 2}, {0, 3, 6}, {0, 4, 7}, {1, 5, 6}, {2, 7, 8},
{3, 9, 10, 13}, {1, 3, 10, 14}, {2, 4, 10, 15}, {4, 11, 16}, {5, 12, 13}, {6, 7, 14, 15},
{8, 16, 17}, {9, 20}, {5, 9, 18, 21}, {6, 10, 18, 22}, {7, 10, 19, 23}, {8, 11, 19, 24},
{11, 25}, {13, 14, 21, 22}, {15, 16, 23, 24}, {12, 26, 29}, {13, 18, 26, 30}, {14, 18, 27, 31},
{15, 19, 27, 32}, {16, 19, 28, 33}, {17, 28, 34}, {20, 21, 29, 30}, {22, 23, 31, 32}, {24, 25, 33, 34},
{20, 26, 37}, {21, 26, 35, 38}, {22, 27, 35, 39}, {23, 27, 36, 40}, {24, 28, 36, 41}, {25, 28, 42},
{30, 31, 38, 39}, {32, 33, 40, 41}, {29, 43, 46}, {30, 35, 43, 47}, {31, 35, 44, 48},
{32, 36, 44, 49}, {33, 36, 45, 50}, {34, 45, 51}, {37, 38, 46, 47}, {39, 40, 48, 49},
{41, 42, 50, 51}, {37, 43, 54}, {38, 43, 52, 55}, {39, 44, 52, 56}, {40, 44, 53, 57},
{41, 45, 53, 58}, {42, 45, 59}, {47, 48, 55, 56}, {49, 50, 57, 58}, {46, 60}, 
{47, 52, 60, 63}, {48, 52, 61, 64}, {49, 53, 61, 65}, {50, 53, 62, 66}, {51, 62},
{54, 55, 63}, {56, 57, 64, 65}, {58, 59, 66}, {55, 60, 67}, {56, 61, 67, 69},
{57, 61, 68, 70}, {58, 62, 68}, {63, 64, 69}, {65, 66, 70}, {64, 67, 71}, {65, 68, 71},
{69, 70}};

const vector<vector<int>> vertex_neighbors = {{0, 1}, {0, 3, 3}, {1, 4, 4}, {3, 2, 3}, {4, 4, 5},
{2, 7, 7}, {3, 3, 8, 8}, {4, 4, 9, 9}, {5, 10, 10}, {7, 6, 7}, {8, 9, 8, 9}, {10, 10, 11}, {6, 12},
{7, 7, 13, 13}, {8, 8, 14, 14}, {9, 9, 15, 15}, {10, 10, 16, 16}, {11, 17}, {13, 14, 13, 14},
{15, 16, 15, 16}, {12, 18, 18}, {13, 13, 19, 19}, {14, 14, 20, 20}, {15, 15, 21, 21}, {16, 16, 22, 22},
{17, 23, 23}, {18, 19, 18, 19}, {20, 21, 20, 21},  {22, 23, 22, 23}, {18, 18, 24}, {19, 19, 25, 25},
{20, 20, 26, 26}, {21, 21, 27, 27}, {22, 22, 28, 28}, {23, 23, 29}, {25, 26, 25, 26}, {27, 28, 27, 28},
{24, 30, 30}, {25, 25, 31, 31}, {26, 26, 32, 32}, {27, 27, 33, 33}, {28, 28, 34, 34}, {29, 35, 35},
{30, 31, 30, 31}, {32, 33, 32, 33}, {34, 35, 34, 35}, {30, 30, 36}, {31, 31, 37, 37},
{32, 32, 38, 38}, {33, 33, 39, 39}, {34, 34, 40, 40}, {35, 35, 41}, {37, 38, 37, 38},
{39, 40, 39, 40}, {36, 42}, {37, 37, 43, 43}, {38, 38, 44, 44}, {39, 39, 45, 45},
{40, 40, 46, 46}, {41, 47}, {42, 43, 43}, {44, 45, 44, 45}, {46, 47, 46}, {43, 43, 48},
{44, 44, 49, 49}, {45, 45, 50, 50}, {46, 46, 51}, {48, 49, 49}, {50, 51, 50},
{49, 49, 52}, {50, 50, 53}, {52, 53}};

const string builders[4] = {"B","R","O","Y"};

Edge::Edge(int location) : pos{location}, owner_index{-1}, neighborVertex{vertex_neighbors[location]},
neighborEdges{edge_neighbors[location]} {};

void Edge::colonize(int builder_index) {
    owner_index = builder_index;
}

string Edge::getIn() {
    if (owner_index == -1) {
        if (pos < 10) {
			return " " + to_string(pos);
		}
        return to_string(pos);
    } else {
        return  builders[owner_index] + "R";
    }
}

