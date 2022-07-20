#ifndef BUILDER_H
#define BUILDER_H
#include <string>
#include <vector>

class Builder {
    std::string colour;// Blue/Red/Orange/Yellow
    int playerNum; // player number
    int buildingPoints; // points for the builder up to 10
    int resourcesType[5];
    // resources[0] = # brick;
    // resources[1] = # energy;
    // resources[2] = # glass;
    // resources[3] = # heat;
    // resources[4] = # wifi;
               
    Builder(int playerNum); //initializes the builder and takes in the player number (0,1,2,3)
    bool basementCanBuild(); // decide if there is enough resources for a basement
    bool roadCanBuild(); // decide if there is enough resources for a road
    bool towerCanBuild(); // decide if there is enough resources for a tower
    void gooseMoving(int pos); 
    void getInfo(); // call when a status of a builder is printed, output message
    void loseResources(); //call on all builders when a 7 is rolled
    //void improveResources(int type, int num);
    //bool improveResidences(int pos, int residenceLevel);
    //void steal(std::string current_builder, 
    //std::string steal_from, int &amount, int &stolen_index);
    // void storeStolen(int &amount, int &stolen_index);

};

#endif
