#include "board.h"
#include <iostream>
using namespace std;

void Board::init() {
    curTurn = 0;
    win = false;
    tiles.resize(19);
    for (int t = 0; t < 19; ++t) {
        tiles[t].tilesInitialization(t);
        tiles[t].geese = false;
        tiles[t].pos = t;
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
    if (builders[player].basementCanBuild() == false) { //not enough resources
    cout << "You do not have enough resources." << endl;
        return false;
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
    builders[player].basementBuild();
}

bool Board::canBuildRoad(int road_index, int player) {
    if (roads[road_index].owner_index != -1) {
        return false;
    }
    if (builders[player].roadCanBuild() == false) { //not enough resources
    cout << "You do not have enough resources." << endl;
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
    builders[player].roadBuild();
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

string Board::GeeseStr(int index) {
    if (index == goose_location) {
        return "GEESE";
    }
    return "     ";
}

void Board::loadedDice() {
    cout << "Input a roll between 2 and 12:" << endl;// H
    int n;
    while (true) {
        if (!(cin >> n)) {
            cout << "Invalid roll." << endl;
        } else if (n < 2 && n > 12) {
            cout << "Invalid roll." << endl;
        } else {
            cin >> n;
            cout << colours[curTurn] << " has rolled a " << n << "." <<endl;
            break;
        }
    }
    if (n == 7) {
        SevenRolled(); //removes resources if necessary and produces output - Dani
        moveGeese(n);
    } else {
        distribution(n);
    }        
}
    

   
void Board::rollDice() {
    if (dice_modes[curTurn] == 0) {
        loadedDice();
    } else {
        fairDice();
    }
} 

// void Board::fairDice() {
//     default_random_engine num = rng;
//     int n = distribution(num);

// }



void Board::printBoard() {
    cout << "                          |"+vertices[0].getIn()+"|--"+roads[0].getIn()+"--|"+vertices[1].getIn()+"|" << endl;
    cout << "                            |         |" << endl;
    cout << "                           "+roads[1].getIn()+"    0   "+roads[2].getIn()+"" << endl;
    cout << "                            |  BRICK  |" << endl;
    cout << "                |"+vertices[2].getIn()+"|--"+roads[3].getIn()+"--|"+vertices[3].getIn()+"|   3  |"+vertices[4].getIn()+"|--"+roads[4].getIn()+"--|"+vertices[5].getIn()+"|" << endl;
    cout << "                  |         |  "+GeeseStr(0)+"  |         |" << endl;
    cout << "                 "+roads[5].getIn()+"    1   "+roads[6].getIn()+"        "+roads[7].getIn()+"    2   "+roads[8].getIn()+"" << endl;
    cout << "                  | ENERGY  |         |  HEAT   |" << endl;
    cout << "      |"+vertices[6].getIn()+"|--"+roads[9].getIn()+"--|"+vertices[7].getIn()+"|  10  |"+vertices[8].getIn()+"|--"+roads[10].getIn()+"--|"+vertices[9].getIn()+"|   5  |"+vertices[10].getIn()+"|--"+roads[11].getIn()+"--|"+vertices[11].getIn()+"|" << endl;
    cout << "        |         |  "+GeeseStr(1)+"  |         |  "+GeeseStr(2)+"  |         |" << endl;
    cout << "       "+roads[12].getIn()+"    3   "+roads[13].getIn()+"        "+roads[14].getIn()+"    4   "+roads[15].getIn()+"        "+roads[16].getIn()+"    5   "+roads[17].getIn()+"" << endl;
    cout << "        | ENERGY  |         |  PARK   |         |  HEAT   |" << endl;
    cout << "      |"+vertices[12].getIn()+"|   4  |"+vertices[13].getIn()+"|--"+roads[18].getIn()+"--|"+vertices[14].getIn()+"|      |"+vertices[15].getIn()+"|--"+roads[19].getIn()+"--|"+vertices[16].getIn()+"|  10  |"+vertices[17].getIn()+"|" << endl;
    cout << "        |  "+GeeseStr(3)+"  |         |  "+GeeseStr(4)+"  |         |  "+GeeseStr(5)+"  |" << endl;
    cout << "       "+roads[20].getIn()+"        "+roads[21].getIn()+"    6   "+roads[22].getIn()+"        "+roads[23].getIn()+"    7   "+roads[24].getIn()+"        "+roads[25].getIn()+"" << endl;
    cout << "        |         |  GLASS  |         |  BRICK  |         |" << endl;
    cout << "      |"+vertices[18].getIn()+"|--"+roads[26].getIn()+"--|"+vertices[19].getIn()+"|  11  |"+vertices[20].getIn()+"|--"+roads[27].getIn()+"--|"+vertices[21].getIn()+"|   3  |"+vertices[22].getIn()+"|--"+roads[28].getIn()+"--|"+vertices[23].getIn()+"|" << endl;
    cout << "        |         |  "+GeeseStr(6)+"  |         |  "+GeeseStr(7)+"  |         |" << endl;
    cout << "       "+roads[29].getIn()+"    8   "+roads[30].getIn()+"        "+roads[31].getIn()+"    9   "+roads[32].getIn()+"        "+roads[33].getIn()+"   10   "+roads[34].getIn()+"" << endl;
    cout << "        |  HEAT   |         |  BRICK  |         |  BRICK  |" << endl;
    cout << "      |"+vertices[24].getIn()+"|   8  |"+vertices[25].getIn()+"|--"+roads[35].getIn()+"--|"+vertices[26].getIn()+"|   2  |"+vertices[27].getIn()+"|--"+roads[36].getIn()+"--|"+vertices[28].getIn()+"|   6  |"+vertices[29].getIn()+"|" << endl;
    cout << "        |  "+GeeseStr(8)+"  |         |  "+GeeseStr(9)+"  |         |  "+GeeseStr(10)+"  |" << endl;
    cout << "       "+roads[37].getIn()+"        "+roads[38].getIn()+"   11   "+roads[39].getIn()+"        "+roads[40].getIn()+"   12   "+roads[41].getIn()+"        "+roads[42].getIn()+"" << endl;
    cout << "        |         | ENERGY  |         |  WIFI   |         |" << endl;
    cout << "      |"+vertices[30].getIn()+"|--"+roads[43].getIn()+"--|"+vertices[31].getIn()+"|   8  |"+vertices[32].getIn()+"|--"+roads[44].getIn()+"--|"+vertices[33].getIn()+"|  12  |"+vertices[34].getIn()+"|--"+roads[45].getIn()+"--|"+vertices[35].getIn()+"|" << endl;
    cout << "        |         |  "+GeeseStr(11)+"  |         |  "+GeeseStr(12)+"  |         |" << endl;
    cout << "       "+roads[46].getIn()+"   13   "+roads[47].getIn()+"        "+roads[48].getIn()+"   14   "+roads[49].getIn()+"        "+roads[50].getIn()+"   15   "+roads[51].getIn()+"" << endl;
    cout << "        | ENERGY  |         |  WIFI   |         |  GLASS  |" << endl;
    cout << "      |"+vertices[36].getIn()+"|   5  |"+vertices[37].getIn()+"|--"+roads[52].getIn()+"--|"+vertices[38].getIn()+"|  11  |"+vertices[39].getIn()+"|--"+roads[53].getIn()+"--|"+vertices[40].getIn()+"|   4  |"+vertices[41].getIn()+"|" << endl;
    cout << "        |  "+GeeseStr(13)+"  |         |  "+GeeseStr(14)+"  |         |  "+GeeseStr(15)+"  |" << endl;
    cout << "       "+roads[54].getIn()+"        "+roads[55].getIn()+"   16   "+roads[56].getIn()+"        "+roads[57].getIn()+"   17   "+roads[58].getIn()+"        "+roads[59].getIn()+"" << endl;
    cout << "        |         |  WIFI   |         |  GLASS  |         |" << endl;
    cout << "      |"+vertices[42].getIn()+"|--"+roads[60].getIn()+"--|"+vertices[43].getIn()+"|   6  |"+vertices[44].getIn()+"|--"+roads[61].getIn()+"--|"+vertices[45].getIn()+"|   9  |"+vertices[46].getIn()+"|--"+roads[62].getIn()+"--|"+vertices[47].getIn()+"|" << endl;
    cout << "                  |  "+GeeseStr(16)+"  |         |  "+GeeseStr(17)+"  |" << endl;
    cout << "                 "+roads[63].getIn()+"        "+roads[64].getIn()+"   18   "+roads[65].getIn()+"        "+roads[66].getIn()+"" << endl;
    cout << "                  |         |  GLASS  |         |" << endl;
    cout << "                |"+vertices[48].getIn()+"|--"+roads[67].getIn()+"--|"+vertices[49].getIn()+"|   9  |"+vertices[50].getIn()+"|--"+roads[68].getIn()+"--|"+vertices[51].getIn()+"|" << endl;
    cout << "                            |  "+GeeseStr(18)+"  |" << endl;
    cout << "                           "+roads[69].getIn()+"        "+roads[70].getIn()+"" << endl;
    cout << "                            |         |" << endl;
    cout << "                          |"+vertices[52].getIn()+"|--"+roads[71].getIn()+"--|"+vertices[53].getIn()+"|" << endl;
}

void Board::status() { // - dani completed
    for (int i = 0; i < 4; i++) {
        builders[i].getInfo();
    }
}

void Board::printHelp() { //done
    cout << "Valid commands:" << endl;
    cout << "board" << endl;
    cout << "status" << endl;
    cout << "residences" << endl;
    cout << "build-road <edge#>" << endl;
    cout << "build-res <housing#>" << endl;
    cout << "improve <housing#>" << endl;
    cout << "trade <colour> <give> <take>" << endl;
    cout << "next" << endl;
    cout << "save <file>" << endl;
    cout << "help" << endl;
}

void Board::SevenRolled() { // called to remove resources of builders -- done
    for (int i = 0; i < 4; i++) {
        builders[i].loseResources();
    }
} 

void Board::trade(int color, int give, int take){ // Dani -- done
    cout << colours[curTurn] << " offers " << colours[color] << 
    " one " << types[give] << " for one " << types[take] << "." << endl;
    cout << "Does " << colours[color] << " accept this offer?" << endl;

    string input = "";
    cin >> input;
    if (input == "yes") {
        if ((builders[curTurn].resourcesType[give] < 1) || (builders[color].resourcesType[take] < 1)){
            cout << "Builder does not have enough resources for the given trade." << endl;
        }
        else {
            builders[curTurn].resourcesType[give] -= 1;
            builders[curTurn].resourcesType[take] += 1;
            builders[color].resourcesType[give] += 1;
            builders[color].resourcesType[take] -= 1;
        }
    }
}


bool Board::canImprove(int vertex_index, int player) {
    if (vertices[vertex_index].residenceLevel == 3) {
        return false;
    }
    if (vertices[vertex_index].owner_index != player) {
        return false;
    }
    return true;
}

void Board::improve(int vertex_index, int player) {
    vertices[vertex_index].upgrade();
}

bool Board::canFirst8(int vertex_index, int player) {
    if (vertices[vertex_index].owner_index != -1) {
        return false;
    }
    for(auto ind_1: vertices[vertex_index].neighbor) {
        if (vertices[ind_1].owner_index != -1) {
            return false;
        }
    }
    return true;
}
