#ifndef DICE_H
#define DICE_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


class Dice {
    virtual bool roll(default_random_engine &rng);
};


class Loaded: public Dice {

};


class Fair: public Dice {

};

#endif