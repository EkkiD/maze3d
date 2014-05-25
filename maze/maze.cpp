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
    if (w_wall.isVisible()) {
        w_wall.render(MVP, M);
    }
    if (n_wall.isVisible()) {
        n_wall.render(MVP, M);
    }
}

void Cell::tearDown(int direction) {
    m_wall_bitmask ^= direction;
    
    if (direction & NORTH) {
        n_wall.knockDown();
    } else if (direction & WEST) {
        w_wall.knockDown();
    }
}


Maze::Maze() { 
    m_cells.reserve(100); 
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            m_cells.push_back(Cell(i, j));
        }
    }

    for (int row = 0; row < NUM_ROWS; row++) {
        m_side_walls.push_back(Wall());
        m_side_walls.back().translate(NUM_COLS - 5 - 0.05, 0, row - 5 + 0.1);
        m_side_walls.back().scale(0.1, 1.0, 0.8);
    }

    for (int col = 0; col < NUM_COLS; col++) {
        m_side_walls.push_back(Wall());
        m_side_walls.back().translate(col - 5 - 0.05, 0, NUM_ROWS - 5 + 0.1);
        m_side_walls.back().scale(0.8, 1.0, 0.1);
    }
}

void Maze::tearDown(int row, int col, bool north) {
    int index = (row * NUM_COLS) + col;
    m_cells[index].tearDown(north ? NORTH : WEST);
}
