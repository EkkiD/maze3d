#include <maze/maze.hpp>
#include <maze/wall.hpp>

int Maze::NUM_ROWS = 10;
int Maze::NUM_COLS = 10;

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
}

void Cell::render(glm::mat4 MVP) const {
    w_wall.render(MVP);
    n_wall.render(MVP);
}


Maze::Maze() { 
    m_cells.reserve(100); 
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            m_cells.push_back(Cell(i, j));
        }
    }
}
