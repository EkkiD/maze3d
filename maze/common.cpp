#include <maze/common.hpp>
#include <iostream>

std::ostream& operator << (std::ostream &o, const GridPoint &a)
{
    o << "x: " << a.x << "  y: " << a.y << std::endl;
    return o;
}
