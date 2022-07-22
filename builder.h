#ifndef BUILDER_H
#define BUILDER_H
#include <string>
#include <vector>

class Builder {
    public:
        std::string colour;// Blue/Red/Orange/Yellow
        int playerNum; // player number
        int buildingPoints; // points for the builder up to 10
        int resourcesType[5];
        // resources[0] = # BRICK;
        // resources[1] = # ENERGY;
        // resources[2] = # GLASS;
        // resources[3] = # HEAT;
        // resources[4] = # WIFI;
               
        Builder(int playerNum); //initializes the builder and takes in the player number (0,1,2,3)
        bool basementCanBuild(); // decide if there is enough resources for a basement
        void basementBuild(); // removes resources to build the basement
        bool roadCanBuild(); // decide if there is enough resources for a road
        void roadBuild(); // removes resources to build the road
        bool towerCanBuild(); // decide if there is enough resources for a tower
        void towerBuild(); // removes resources to build the tower
        bool houseCanBuild(); // decide if there is enough resources for a house
        void houseBuild(); // removes resources to build the house
        void getInfo(); // call when a status of a builder is printed, output message
        void loseResources(); //call on all builders when a 7 is rolled
        //void improveResources(int type, int num);
        //bool improveResidences(int pos, int residenceLevel);
        //void steal(std::string current_builder, 
        //std::string steal_from, int &amount, int &stolen_index);
        // void storeStolen(int &amount, int &stolen_index);

};

#endif
