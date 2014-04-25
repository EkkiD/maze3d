#include <maze/maze.hpp>
#include <maze/wall.hpp>

Cell::Cell(int row, int col): 
    m_row(row), 
    m_col(col),
    n_wall(),
    w_wall() 
{
    w_wall.translate(col - 5 - 0.05, 0, row - 5 + 0.1);
    w_wall.scale(0.1, 1.0, 0.8);

    n_wall.translate(col - 5 + 0.1, 0, row - 5 - 0.05);
    n_wall.scale(0.8, 1.0, 0.1);
    m_wall_bitmask = NORTH | SOUTH | EAST | WEST;
}

void Cell::render(glm::mat4 MVP, glm::mat4 M) const {
    if (m_wall_bitmask & WEST) {
        w_wall.render(MVP, M);
    }
    if (m_wall_bitmask & NORTH) {
        n_wall.render(MVP, M);
    }
}

void Cell::tearDown(int direction) {
    m_wall_bitmask ^= direction;
}


Maze::Maze() { 
    m_cells.reserve(100); 
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            m_cells.push_back(Cell(i, j));
        }
    }
}

void Maze::tearDown(int row, int col, bool north) {
    int index = (row * NUM_COLS) + col;
    m_cells[index].tearDown(north ? NORTH : WEST);
}
