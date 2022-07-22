#include <string>
#include <vector>
#include <iostream>
#include "builder.h"
using namespace std;

Builder::Builder(int playerNum) : playerNum{playerNum}, buildingPoints{0} {
    for (int i = 0; i < 4; i++) {
        resourcesType[i] = 0;
    }
    if (playerNum == 0){
        colour = "Blue";
    }
    else if (playerNum == 1){
        colour = "Red";
    }
    else if (playerNum == 2){
        colour = "Orange";
    }
    else if (playerNum == 3){
        colour = "Yellow";
    }
    else {
        cout << "error in builder::constructor()" << endl;
    }
}
bool Builder::roadCanBuild(){
    if ((resourcesType[4] < 1) || (resourcesType[3] < 1)) {
        return false; //not enough resources
    }
    return true;
}
void Builder::roadBuild(){
    this->resourcesType[4] -= 1;
    this->resourcesType[3] -= 1;
}
bool Builder::basementCanBuild(){
    if ((resourcesType[0] < 1) || (resourcesType[1] < 1) 
    || (resourcesType[2] < 1) || (resourcesType[4] < 1)) {
        return false; //not enough resources
    }
    return true;
}

void Builder::basementBuild(){
    this->resourcesType[0] -= 1;
    this->resourcesType[1] -= 1;
    this->resourcesType[2] -= 1;
    this->resourcesType[4] -= 1;
    buildingPoints++;
}

bool Builder::towerCanBuild(){
    if ((resourcesType[0] < 3) || (resourcesType[1] < 2) 
    || (resourcesType[2] < 2) || (resourcesType[4] < 1) || (resourcesType[3] < 2)) {
        return false; //not enough resources
    }
    return true;
}
void Builder::towerBuild(){
    this->resourcesType[0] -= 3;
    this->resourcesType[1] -= 2;
    this->resourcesType[2] -= 2;
    this->resourcesType[3] -= 2;
    this->resourcesType[4] -= 1;
    buildingPoints++;
} 

bool Builder::houseCanBuild(){
    if ((resourcesType[2] < 2) || (resourcesType[3] < 3)) {
        return false; //not enough resources
    }
    return true;
}
void Builder::houseBuild(){
    this->resourcesType[2] -= 2;
    this->resourcesType[3] -= 3;
    buildingPoints++;
} 


//void Builder::improveResources(int type, int num){}
//bool Builder::improveResidences(int pos, int residenceLevel){}

void Builder::getInfo(){
    cout << colour << " has " << buildingPoints << " building points, " << resourcesType[0]
    << " brick, " << resourcesType[1] << " energy, " << resourcesType[2] << " glass, "
    << resourcesType[3] << " heat, and " << resourcesType[4] << " Wifi." << endl;
}
    
void Builder::loseResources(){
    int total_resources = 0;
    for (int i = 0; i < 5; i++) {
        total_resources += resourcesType[i];
    }
    if (total_resources < 10) {
        return;
    }
    int removed_resources[5] = {0, 0, 0, 0, 0};
    int remove = total_resources/2;

    while(remove > 0) {
        for (int i = 0; i < 5; i++) {
            if (resourcesType[i] > 0) {
            resourcesType[i] -= 1;
            removed_resources[i] += 1;
            remove--;
            }
        }
        if (remove == 0) {
            break;
        }
    }
    cout << "Builder " << colour << " loses " << total_resources/2 << " to the geese. They lose:" << endl;
    for (int i = 0; i < 5; i++) {
        if (removed_resources[i] > 0) {
            cout << removed_resources[i] << " ";
            if (i = 0) {
                cout << "BRICK" << endl;
            }
            else if (i = 1) {
                cout << "ENERGY" << endl;
            }
            else if (i = 2) {
                cout << "GLASS" << endl;
            }
            else if (i = 3) {
                cout << "HEAT" << endl;
            }
            else if (i = 4) {
                cout << "WIFI" << endl;
            }
        }
    }
}


