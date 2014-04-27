#ifndef __COMMON_HPP__
#define __COMMON_HPP__

enum STATUS { 
    UNTOUCHED,
    VISITED,
    STACKED,
    CURRENT
};

struct GridPoint {
    int x;
    int y;
};

const char NORTH = 1;
const char EAST = 2;
const char SOUTH = 4;
const char WEST = 8;

#endif
