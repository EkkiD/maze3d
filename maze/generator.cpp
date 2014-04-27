#include <maze/generator.hpp>


bool DFSGenerator::setStartLoc(GridPoint point) {
    m_stack.push_back(point);
}

bool DFSGenerator::step() {
}
