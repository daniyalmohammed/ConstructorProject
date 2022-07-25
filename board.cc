#include "board.h"
using namespace std;

void Board::init() {
    loadout = "0 3 1 10 3 5 1 4 5 7 3 10 2 11 0 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 2 4 4 6 2 9 2 9";
    for (int i = 0; i < 4; i++) {
        dice_modes[i] = 0;
    }
    curTurn = 0;
    win = false;
    for (int t = 0; t < 19; ++t) {
        tiles.emplace_back(Tile{t});
    }
    tiles[4].geese = true;
    goose_location = 4;
    for (int r = 0; r < 72; ++r) {
        roads.emplace_back(Edge{r});
    }
    for (int v = 0; v < 54; ++v) {
        vertices.emplace_back(Vertex{v});
    }
    for (int b = 0; b < 4; ++b) {
        builders.emplace_back(Builder{b});
    }
}

bool Board::canBuild(int vertex_index) {
    if (vertices[vertex_index].owner_index != -1) {
        cout << "You cannot build here." << endl;
        return false;
    }
    for(auto ind_1: vertices[vertex_index].neighbor) {
        if (vertices[ind_1].owner_index != -1) {
            cout << "You cannot build here." << endl;
            return false;
        }
    }
    if (builders[curTurn].basementCanBuild() == false) { //not enough resources
    cout << "You do not have enough resources." << endl;
        return false;
    }
    for(auto ind_2: vertices[vertex_index].my_roads) {
        if (roads[ind_2].owner_index == curTurn) {
            return true;
        }
    }
    cout << "You cannot build here." << endl;
    return false;
}

void Board::build(int vertex_index) {
    vertices[vertex_index].colonize(curTurn);
    builders[curTurn].basementBuild();
}

bool Board::canBuildRoad(int road_index) {
    if (roads[road_index].owner_index != -1) {
        cout << "You cannot build here." << endl;
        return false;
    }
    if (builders[curTurn].roadCanBuild() == false) { //not enough resources
    cout << "You do not have enough resources." << endl;
        return false;
    }
    for(auto ind_1 : roads[road_index].neighborVertex) {
        if (vertices[ind_1].owner_index == curTurn) {
            return true;
        }
    }
    for (size_t i = 0; i < roads[road_index].neighborEdges.size(); ++i) {
        if (roads[roads[road_index].neighborEdges[i]].owner_index == curTurn) {
            if ( vertices[roads[road_index].neighborVertex[i]].owner_index == -1) {
                return true;
            }
        }
    }
    cout << "You cannot build here." << endl;
    return false;
}


void Board::buildRoad(int road_index) {
    roads[road_index].colonize(curTurn);
    builders[curTurn].roadBuild();
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

int Board::material_to_index(string material) {
    if (material == "BRICK") {
        return 0;
    }
    if (material == "ENERGY") {
        return 1;
    }
    if (material == "GLASS") {
        return 2;
    }
    if (material == "HEAT") {
        return 3;
    }
    if (material == "WIFI") {
        return 4;
    }
    if (material == "PARK") {
        return 5;
    }
    else {
        return -1;
    }
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
            cout << "Input a roll between 2 and 12:" << endl;// H
        } else if (n < 2 || n > 12) {
            cout << "Invalid roll." << endl;
            cout << "Input a roll between 2 and 12:" << endl;// H
        } else {
            cout << colours[curTurn] << " has rolled a " << n << "." <<endl;
            break;
        }
    }
    if (n == 7) {
        SevenRolled(); //removes resources if necessary and produces output - Dani
        moveGeese();
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

void Board::fairDice() {
    uniform_int_distribution<int> pic(1,6);
    int n_1 = pic(rng);
    int n_2 = pic(rng);
    int n = n_1 + n_2;
    cout << n << " has been rolled." << endl;
    if (n == 7) {
	    moveGeese();
    } else {
	    distribution(n);
    }
}



void Board::printBoard() {
    cout << "                          |"+vertices[0].getIn()+"|--"+roads[0].getIn()+"--|"+vertices[1].getIn()+"|" << endl;
    cout << "                            |         |" << endl;
    cout << "                           "+roads[1].getIn()+"    0   "+roads[2].getIn()+"" << endl;
    cout << "                            |"+ tiles[0].to_s() +"|" << endl;
    cout << "                |"+vertices[2].getIn()+"|--"+roads[3].getIn()+"--|"+vertices[3].getIn()+"|  "+ tiles[0].c_to_s() +"  |"+vertices[4].getIn()+"|--"+roads[4].getIn()+"--|"+vertices[5].getIn()+"|" << endl;
    cout << "                  |         |  "+GeeseStr(0)+"  |         |" << endl;
    cout << "                 "+roads[5].getIn()+"    1   "+roads[6].getIn()+"        "+roads[7].getIn()+"    2   "+roads[8].getIn()+"" << endl;
    cout << "                  |"+ tiles[1].to_s() +"|         |"+ tiles[2].to_s() +"|" << endl;
    cout << "      |"+vertices[6].getIn()+"|--"+roads[9].getIn()+"--|"+vertices[7].getIn()+"|  "+ tiles[1].c_to_s() +"  |"+vertices[8].getIn()+"|--"+roads[10].getIn()+"--|"+vertices[9].getIn()+"|  "+ tiles[2].c_to_s() +"  |"+vertices[10].getIn()+"|--"+roads[11].getIn()+"--|"+vertices[11].getIn()+"|" << endl;
    cout << "        |         |  "+GeeseStr(1)+"  |         |  "+GeeseStr(2)+"  |         |" << endl;
    cout << "       "+roads[12].getIn()+"    3   "+roads[13].getIn()+"        "+roads[14].getIn()+"    4   "+roads[15].getIn()+"        "+roads[16].getIn()+"    5   "+roads[17].getIn()+"" << endl;
    cout << "        |"+ tiles[3].to_s() +"|         |"+ tiles[4].to_s() +"|         |"+ tiles[5].to_s() +"|" << endl;
    cout << "      |"+vertices[12].getIn()+"|  "+ tiles[3].c_to_s() +"  |"+vertices[13].getIn()+"|--"+roads[18].getIn()+"--|"+vertices[14].getIn()+"|  "+ tiles[4].c_to_s() +"  |"+vertices[15].getIn()+"|--"+roads[19].getIn()+"--|"+vertices[16].getIn()+"|  "+ tiles[5].c_to_s() +"  |"+vertices[17].getIn()+"|" << endl;
    cout << "        |  "+GeeseStr(3)+"  |         |  "+GeeseStr(4)+"  |         |  "+GeeseStr(5)+"  |" << endl;
    cout << "       "+roads[20].getIn()+"        "+roads[21].getIn()+"    6   "+roads[22].getIn()+"        "+roads[23].getIn()+"    7   "+roads[24].getIn()+"        "+roads[25].getIn()+"" << endl;
    cout << "        |         |"+ tiles[6].to_s() +"|         |"+ tiles[7].to_s() +"|         |" << endl;
    cout << "      |"+vertices[18].getIn()+"|--"+roads[26].getIn()+"--|"+vertices[19].getIn()+"|  "+ tiles[6].c_to_s() +"  |"+vertices[20].getIn()+"|--"+roads[27].getIn()+"--|"+vertices[21].getIn()+"|  "+ tiles[7].c_to_s() +"  |"+vertices[22].getIn()+"|--"+roads[28].getIn()+"--|"+vertices[23].getIn()+"|" << endl;
    cout << "        |         |  "+GeeseStr(6)+"  |         |  "+GeeseStr(7)+"  |         |" << endl;
    cout << "       "+roads[29].getIn()+"    8   "+roads[30].getIn()+"        "+roads[31].getIn()+"    9   "+roads[32].getIn()+"        "+roads[33].getIn()+"   10   "+roads[34].getIn()+"" << endl;
    cout << "        |"+ tiles[8].to_s() +"|         |"+ tiles[9].to_s() +"|         |"+ tiles[10].to_s() +"|" << endl;
    cout << "      |"+vertices[24].getIn()+"|  "+ tiles[8].c_to_s() +"  |"+vertices[25].getIn()+"|--"+roads[35].getIn()+"--|"+vertices[26].getIn()+"|  "+ tiles[9].c_to_s() +"  |"+vertices[27].getIn()+"|--"+roads[36].getIn()+"--|"+vertices[28].getIn()+"|  "+ tiles[10].c_to_s() +"  |"+vertices[29].getIn()+"|" << endl;
    cout << "        |  "+GeeseStr(8)+"  |         |  "+GeeseStr(9)+"  |         |  "+GeeseStr(10)+"  |" << endl;
    cout << "       "+roads[37].getIn()+"        "+roads[38].getIn()+"   11   "+roads[39].getIn()+"        "+roads[40].getIn()+"   12   "+roads[41].getIn()+"        "+roads[42].getIn()+"" << endl;
    cout << "        |         |"+ tiles[11].to_s() +"|         |"+ tiles[12].to_s() +"|         |" << endl;
    cout << "      |"+vertices[30].getIn()+"|--"+roads[43].getIn()+"--|"+vertices[31].getIn()+"|  "+ tiles[11].c_to_s() +"  |"+vertices[32].getIn()+"|--"+roads[44].getIn()+"--|"+vertices[33].getIn()+"|  "+ tiles[12].c_to_s() +"  |"+vertices[34].getIn()+"|--"+roads[45].getIn()+"--|"+vertices[35].getIn()+"|" << endl;
    cout << "        |         |  "+GeeseStr(11)+"  |         |  "+GeeseStr(12)+"  |         |" << endl;
    cout << "       "+roads[46].getIn()+"   13   "+roads[47].getIn()+"        "+roads[48].getIn()+"   14   "+roads[49].getIn()+"        "+roads[50].getIn()+"   15   "+roads[51].getIn()+"" << endl;
    cout << "        |"+ tiles[13].to_s() +"|         |"+ tiles[14].to_s() +"|         |"+ tiles[15].to_s() +"|" << endl;
    cout << "      |"+vertices[36].getIn()+"|  "+ tiles[13].c_to_s() +"  |"+vertices[37].getIn()+"|--"+roads[52].getIn()+"--|"+vertices[38].getIn()+"|  "+ tiles[14].c_to_s() +"  |"+vertices[39].getIn()+"|--"+roads[53].getIn()+"--|"+vertices[40].getIn()+"|  "+ tiles[15].c_to_s() +"  |"+vertices[41].getIn()+"|" << endl;
    cout << "        |  "+GeeseStr(13)+"  |         |  "+GeeseStr(14)+"  |         |  "+GeeseStr(15)+"  |" << endl;
    cout << "       "+roads[54].getIn()+"        "+roads[55].getIn()+"   16   "+roads[56].getIn()+"        "+roads[57].getIn()+"   17   "+roads[58].getIn()+"        "+roads[59].getIn()+"" << endl;
    cout << "        |         |"+ tiles[16].to_s() +"|         |"+ tiles[17].to_s() +"|         |" << endl;
    cout << "      |"+vertices[42].getIn()+"|--"+roads[60].getIn()+"--|"+vertices[43].getIn()+"|  "+ tiles[16].c_to_s() +"  |"+vertices[44].getIn()+"|--"+roads[61].getIn()+"--|"+vertices[45].getIn()+"|  "+ tiles[17].c_to_s() +"  |"+vertices[46].getIn()+"|--"+roads[62].getIn()+"--|"+vertices[47].getIn()+"|" << endl;
    cout << "                  |  "+GeeseStr(16)+"  |         |  "+GeeseStr(17)+"  |" << endl;
    cout << "                 "+roads[63].getIn()+"        "+roads[64].getIn()+"   18   "+roads[65].getIn()+"        "+roads[66].getIn()+"" << endl;
    cout << "                  |         |"+ tiles[18].to_s() +"|         |" << endl;
    cout << "                |"+vertices[48].getIn()+"|--"+roads[67].getIn()+"--|"+vertices[49].getIn()+"|  "+ tiles[18].c_to_s() +"  |"+vertices[50].getIn()+"|--"+roads[68].getIn()+"--|"+vertices[51].getIn()+"|" << endl;
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

void Board::helpCommandsPrint() { //done
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

void Board::trade(string color, string give, string take){ // Dani -- done

    cout << colours[curTurn] << " offers " << color << 
    " one " << give << " for one " << take << "." << endl;
    cout << "Does " << color << " accept this offer?" << endl;

    int num_colour = colour_to_index(color);
    int give_int = material_to_index(give);
    int take_int = material_to_index(take);

    string input = "";
    cin >> input;
    if (input == "yes") {
        if ((builders[curTurn].resourcesType[give_int] < 1) || (builders[num_colour].resourcesType[take_int] < 1)){
            cout << "Builder does not have enough resources for the given trade." << endl;
        }
        else {
            builders[curTurn].resourcesType[give_int] -= 1;
            builders[curTurn].resourcesType[take_int] += 1;
            builders[num_colour].resourcesType[give_int] += 1;
            builders[num_colour].resourcesType[take_int] -= 1;
        }
    }
}


bool Board::canImprove(int vertex_index) {
    if (vertices[vertex_index].residenceLevel == 3) {
        return false;
    }
    else if (vertices[vertex_index].owner_index != curTurn) {
        return false;
    }
    else if (vertices[vertex_index].residenceLevel == 1) {
        return builders[curTurn].houseCanBuild();
    }
    else if (vertices[vertex_index].residenceLevel == 2) {
        return builders[curTurn].towerCanBuild();
    }
    else {
        cout << "check Board::canImprove for bugs" << endl;
        return false;
    }
}

void Board::improve(int vertex_index) {
    if (vertices[vertex_index].residenceLevel == 1) {
        builders[curTurn].houseBuild();
    }
    else if (vertices[vertex_index].residenceLevel == 2) {
        builders[curTurn].towerBuild();
    }
    vertices[vertex_index].upgrade();
}

bool Board::canFirst8(int vertex_index) {
    if (vertices[vertex_index].owner_index != -1) {
        cout << "You cannot build here." << endl;
        return false;
    }
    for(auto ind_1: vertices[vertex_index].neighbor) {
        if (vertices[ind_1].owner_index != -1) {
            cout << "You cannot build here." << endl;
            return false;
        }
    }
    return true;
}


void Board::moveGeese() {
    int index;
    cin >> index;
    cout << "Choose where to place the GEESE." << endl;
    tiles[goose_location].geese = false;
    tiles[index].geese = true;
    goose_location = index;
    vector<bool> Here = {false, false, false, false};
    for(auto ind_1: tiles[index].elements) {
        if (vertices[ind_1].owner_index != -1) {
            Here[vertices[ind_1].owner_index] = true;
        }
    }
    Here[curTurn] = false;
    if (Here[0] || Here[1] || Here[2] || Here[3]) {
        string victimes = "";
        vector<string> vect_victims;

        for(int b = 0; b < 4; ++b) {
            if (Here[b] && (builders[b].totalResources() != 0)) {
                if (victimes != "") {
                    victimes += ",";
                }
                victimes += colours[b];
                vect_victims.emplace_back(colours[b]);
            }
        }
        cout << "Builder " + colours[curTurn] + " can choose to steal from " + victimes + "." << endl;
        
        string input;
        cout << "Choose a builder to steal from." << endl;

        while(1) {
            string input = "";
            cin >> input;
            bool is_builder = false;
            for (int i = 0; i < vect_victims.size(); i++) {
                if (input == vect_victims[i]) {
                    is_builder = true;
                }
            }
            if (is_builder) {
                stealResource(colour_to_index(input));
                break;
            }
            else {
                cout << "Not a valid builder to steal from. Try again." << endl;
            }
        }
    } else {
        cout << "Builder " + colours[curTurn] + " has no builders to steal from." << endl;
    }

}

void Board::next() {
    curTurn += 1;
    if (curTurn == 4) {
        curTurn = 0;
    }
    cout << "Builder " << colours[curTurn] << "'s turn." << endl;
    builders[curTurn].getInfo();
    printBoard();
}

void Board::testTile() {
	for (Tile t : tiles) {
		cout << "index is" << " " << t.pos << " ";
        cout << "type is" << " " << t.typeofResources;
		cout << " " << "chance is" << " " << t.chance << endl;
	}
}


void Board::stealResource(int steal_from) { //dani done
    int total_resources = builders[steal_from].totalResources();
    vector<int> randomizer;

    for (int j = 0; j < builders[steal_from].resourcesType[0]; j++) {
            randomizer.emplace_back(0);
    }
    for (int j = 0; j < builders[steal_from].resourcesType[1]; j++) {
            randomizer.emplace_back(1);
    }
    for (int j = 0; j < builders[steal_from].resourcesType[2]; j++) {
            randomizer.emplace_back(2);
    }
    for (int j = 0; j < builders[steal_from].resourcesType[3]; j++) {
            randomizer.emplace_back(3);
    }

    default_random_engine num = rng;
    uniform_int_distribution<int> pic(0, total_resources - 1);
    int spot = pic(num);
    int resource = randomizer[spot];

    builders[curTurn].resourcesType[resource] += 1;
    builders[steal_from].resourcesType[resource] -= 1;

    cout << "Builder " << colours[curTurn] << "steals "<< types[resource] << 
    " from builder " << colours[steal_from] << "." << endl;

}

void Board::distribution(int n) {
    bool give = false;
    vector<vector<int>> getting = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    for(auto T : tiles) {
        if (T.chance == n) {
            for (auto ind : T.elements) {
                if (vertices[ind].owner_index != -1) {
                    getting[vertices[ind].owner_index][T.typeofResources] += vertices[ind].residenceLevel;
                    give = true;
                }
            }
        }
    }
    if (give == true) {
        for (int player = 0; player < 4; player++) {
            int resources[5] = {0, 0, 0, 0, 0};
            for (int resource = 0; resource < 5; resource++) {
                builders[player].resourcesType[resource] += getting[player][resource];
                resources[resource] += getting[player][resource];
            }
            bool did_gain = false;
            for (int resource = 0; resource < 5; resource++) {
                if (resources[resource] > 0) {
                    if (!did_gain) {
                    cout << "Builder " << colours[player] << " gained: " << endl;
                    did_gain = true;
                    }
                    cout << resources[resource] << " " << types[resource] << endl;
                }
            }
        }
    } else {
        cout << "No builders gained resources." << endl;
        return;
    }
}

void Board::first8() {
    int arr[8] = {0,1,2,3,3,2,1,0};
    for (int i = 0; i < 8; i++) {
        bool checking = false;
        cout << "Builder" << " ";
        cout << colours[arr[i]] << ", ";
        cout << "where do you want to build a basement?" << endl;
        int num;
        while (! checking) {
		    cin >> num;
            checking = canFirst8(num);
        }
		//builders[arr[i]].basement.emplace_back(num);
		builders[arr[i]].buildingPoints += 1;
        vertices[num].colonize(arr[i]);
	}
    printBoard();
    cout << "Builder " << colours[curTurn] << "'s turn." << endl;
    builders[curTurn].getInfo();

}

void Board::save(string file_name) {
    ofstream outfile{ file_name };
    outfile << to_string(curTurn) << endl;
    vector<vector<int>> owners_pos = {{},{},{},{}};
    vector<vector<int>> owners_lv = {{},{},{},{}};
    for(auto v : vertices) {
        if (v.owner_index != -1) {
            owners_pos[v.owner_index].emplace_back(v.pos);
            owners_pos[v.owner_index].emplace_back(v.residenceLevel);
        } 
    }
    vector<vector<int>> road_pos = {{},{},{},{}};
    for(auto r : roads) {
        if (r.owner_index != -1) {
            road_pos[r.owner_index].emplace_back(r.pos);
        }
    }
    outfile << builders[0].resourcesType[0] << " ";
    outfile << builders[0].resourcesType[1] << " ";
    outfile << builders[0].resourcesType[2] << " ";
    outfile << builders[0].resourcesType[3] << " ";
    outfile << builders[0].resourcesType[4] << " ";
    outfile << "r ";
    for (auto r_0 : road_pos[0]) {
        outfile << r_0;
        outfile << " ";
    }
    outfile << "h";
    for (int i = 0; i < owners_pos[0].size(); ++ i) {
        outfile << " " << owners_pos[0][i];
        if (owners_lv[0][i] == 1) {
            outfile << " B";
        } else if (owners_lv[0][i] == 2) {
            outfile << " H";
        } else {
            outfile << " T";
        }
    }
    outfile << endl;

    outfile << builders[1].resourcesType[0] << " ";
    outfile << builders[1].resourcesType[1] << " ";
    outfile << builders[1].resourcesType[2] << " ";
    outfile << builders[1].resourcesType[3] << " ";
    outfile << builders[1].resourcesType[4] << " ";
    outfile << "r ";
    for (auto r_1 : road_pos[1]) {
        outfile << r_1;
        outfile << " ";
    }
    outfile << "h";
    for (int j = 0; j < owners_pos[1].size(); ++ j) {
        outfile << " " << owners_pos[1][j];
        if (owners_lv[1][j] == 1) {
            outfile << " B";
        } else if (owners_lv[1][j] == 2) {
            outfile << " H";
        } else {
            outfile << " T";
        }
    }
    outfile << endl;


    outfile << builders[2].resourcesType[0] << " ";
    outfile << builders[2].resourcesType[1] << " ";
    outfile << builders[2].resourcesType[2] << " ";
    outfile << builders[2].resourcesType[3] << " ";
    outfile << builders[2].resourcesType[4] << " ";
    outfile << "r ";
    for (auto r_2 : road_pos[2]) {
        outfile << r_2;
        outfile << " ";
    }
    outfile << "h";
    for (int k = 0; k < owners_pos[2].size(); ++ k) {
        outfile << " " << owners_pos[2][k];
        if (owners_lv[2][k] == 1) {
            outfile << " B";
        } else if (owners_lv[2][k] == 2) {
            outfile << " H";
        } else {
            outfile << " T";
        }
    }
    outfile << endl;

    outfile << builders[3].resourcesType[0] << " ";
    outfile << builders[3].resourcesType[1] << " ";
    outfile << builders[3].resourcesType[2] << " ";
    outfile << builders[3].resourcesType[3] << " ";
    outfile << builders[3].resourcesType[4] << " ";
    outfile << "r ";
    for (auto r_3 : road_pos[3]) {
        outfile << r_3;
        outfile << " ";
    }
    outfile << "h";
    for (int m = 0; m < owners_pos[3].size(); ++ m) {
        outfile << " " << owners_pos[3][m];
        if (owners_lv[3][m] == 1) {
            outfile << " B";
        } else if (owners_lv[3][m] == 2) {
            outfile << " H";
        } else {
            outfile << " T";
        }
    }
    outfile << endl;

    outfile << loadout << endl;
    outfile << goose_location << endl;

}


void Board::getRez() {
    cout << colours[curTurn] << "has built:" << endl;
    for(auto v : vertices) {
        if (v.owner_index == curTurn) {
            cout << (v.pos) << " ";
            if (v.residenceLevel == 1) {
                cout << "B";
            } else if (v.residenceLevel == 2) {
                cout << "H";
            } else {
                cout << "T";
            }
            cout << endl;
        } 
    }
}

void Board::seed(string input) { // assume input is in range of std::stoi
    //vector<int> v;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (input != "") {
        seed = stoi(input);
    }
    rng = default_random_engine{seed};
    for (int i = 0; i < 4; i++) {
        builders[i].rng_b = rng;
    }
}



void Board::loadFile(string file_name) {
    string line;
    ifstream infile{file_name};
    getline(infile, line);
    istringstream iss_0(line);
    int n;
    iss_0 >> n;
    curTurn = n;
    string reader;
    int mat;
    for(int i = 0; i < 4; ++i) {
        getline(infile, line);
        istringstream iss(line);
        iss >> mat;
        builders[i].resourcesType[0] = mat;
        iss >> mat;
        builders[i].resourcesType[1] = mat;
        iss >> mat;
        builders[i].resourcesType[2] = mat;
        iss >> mat;
        builders[i].resourcesType[3] = mat;
        iss >> mat;
        builders[i].resourcesType[4] = mat;
        iss >> reader;
        while (iss >> reader) {
            if (reader == "h") {
                break;
            }
            istringstream iss_2(reader);
            iss_2 >> mat;
            roads[mat].owner_index = i;
        }
        while (iss >> mat) {
            iss >> reader;
            if (reader == "B") {
                vertices[mat].owner_index = i;
                vertices[mat].residenceLevel = 1;
                builders[i].buildingPoints += 1;
            } else if (reader == "H") {
                vertices[mat].owner_index = i;
                vertices[mat].residenceLevel = 2;
                builders[i].buildingPoints += 2;
            } else {
                vertices[mat].owner_index = i;
                vertices[mat].residenceLevel = 3;
                builders[i].buildingPoints += 3;
            }
        }
    }
    getline(infile, line);
    loadout = line;
    istringstream iss_3(line);
    int r;
    int c;
    for (int j = 0; j < 19; ++ j) {
        iss_3 >> r;
        iss_3 >> c;
        if (r == 5) {
            tiles[j].typeofResources = -1;
            tiles[j].chance = -1;
        } else {
            tiles[j].typeofResources = r;
            tiles[j].chance = c;
        }
    }
    getline(infile, line);
    istringstream iss_4(line);
    int g_pos;
    iss_4 >> g_pos;
    tiles[g_pos].geese = true;
    tiles[goose_location].geese = false;
    goose_location = g_pos;
}

bool Board::checkWin(){
    for (int i = 0; i < 4; i++){
        if (builders[i].buildingPoints >= 10){
            cout << "Player " << colours[i] << "wins the game!" << endl;
            return true;
        }
    }
    return false;
}

void Board::loadBoard(string file_name) {
    string line;
    ifstream infile{file_name};
    getline(infile, line);
    loadout = line;
    istringstream iss(line);
    int r;
    int c;
    for (int j = 0; j < 19; ++ j) {
        iss >> r;
        iss >> c;
        if (r == 5) {
            tiles[j].typeofResources = -1;
            tiles[j].chance = -1;
        } else {
            tiles[j].typeofResources = r;
            tiles[j].chance = c;
        }
    }
}

void Board::randomBoard() {
    vector<int> cha = {2,7,12,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    vector<int> types = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5};
    shuffle( cha.begin(), cha.end(), rng );
    shuffle( types.begin(), types.end(), rng );
    int sev_p = -2;
    int five_p = -1;
    for(int ch = 0; ch < 19; ++ch) {
        if (cha[ch] == 7) {
            sev_p = ch;
            break;
        }
    }
    for(int t = 0; t < 19; ++t) {
        if (types[t] == 5) {
            five_p = t;
            break;
        }
    }
    if (sev_p != five_p) {
        int temp = cha[five_p];
        cha[five_p] = 7;
        cha[sev_p] = temp;
    }
    string newloadout = "";
    for (int i = 0; i < 18; ++i) {
        newloadout += to_string(types[i]);
        newloadout += " ";
        newloadout += to_string(cha[i]);
        newloadout += " ";
    }
    newloadout += to_string(types[18]);
    newloadout += " ";
    newloadout += to_string(cha[18]);
    loadout = newloadout;
    istringstream iss(newloadout);
    int r;
    int c;
    for (int j = 0; j < 19; ++ j) {
        iss >> r;
        iss >> c;
        if (r == 5) {
            tiles[j].typeofResources = -1;
            tiles[j].chance = -1;
        } else {
            tiles[j].typeofResources = r;
            tiles[j].chance = c;
        }
    }
}
