#ifndef BUILDER_H
#define BUILDER_H
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

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
        std::vector<int> basement;
        std::vector<int> tower;
        std::vector<int> house;
        std::vector<int> road;
        std::default_random_engine rng_b;
               
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
        int totalResources(); //sums the total number of resources a builder has
};

#endif
