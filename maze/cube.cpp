#include <maze/cube.hpp>
#include <iostream>


void Cube::render() {
    glBindVertexArray(vao);
    // TODO: unhardcode 30
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
}
