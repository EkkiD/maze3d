#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include <iostream>

enum STATUS { 
    UNTOUCHED,
    VISITED,
    STACKED,
    CURRENT
};

struct GridPoint {
    GridPoint(int x, int y) : x(x), y(y) {};
    int x;
    int y;
};

std::ostream& operator << (std::ostream &o, const GridPoint &a);

const unsigned char NORTH = 1;
const unsigned char EAST = 2;
const unsigned char SOUTH = 4;
const unsigned char WEST = 8;

const int NUM_ROWS = 10;
const int NUM_COLS = 10;

#endif
