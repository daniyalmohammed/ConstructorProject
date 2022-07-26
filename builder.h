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
        std::string colour;
        int playerNum; 
        int buildingPoints; 
        int resourcesType[5];
        std::vector<int> basement;
        std::vector<int> tower;
        std::vector<int> house;
        std::vector<int> road;
        std::default_random_engine rng_b;
               
        Builder(int playerNum); 
        bool basementCanBuild(); 
        void basementBuild(); 
        bool roadCanBuild(); 
        void roadBuild(); 
        bool towerCanBuild(); 
        void towerBuild(); 
        bool houseCanBuild(); 
        void houseBuild(); 
        void getInfo(); 
        void loseResources(); 
        int totalResources(); 
};

#endif


