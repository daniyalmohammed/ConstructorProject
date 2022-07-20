#ifndef BUILDER_H
#define BUILDER_H
#include <string>
#include <vector>

class Builder {
    // std::string builder; // current builder(currentTurn), Blue/Red/Orange/Yellow
    int buildingPoints;
    int resourcesType[5]; // resources[0] = # BRICK ...
    // std::vector<int> basements; // current builder's
    // std::vector<int> towers;
    // std::vector<int> houses;
    // std::vector<int> roads;                               
    //Builder(std::string colour, int geeseIndex);
    bool roadCanBuild(); // decide if there is enough resources for a road
    void gooseMoving(int pos);
    void improveResources(int type, int num);
    bool improveResidences(int pos, int residenceLevel);
    
    // void steal(std::string current_builder, 
               // std::string steal_from, int &amount, int &stolen_index);
    // void storeStolen(int &amount, int &stolen_index);
    std::string info(); // 3.7 saving the game
    
    void loseResources();
};

#endif
