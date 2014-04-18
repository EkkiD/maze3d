#include <maze/cube.hpp>
#include <iostream>
#include <maze/opengl.hpp>


void Cube::render() {
    glBindVertexArray(G_CUBE_VAO);
    // TODO: unhardcode 30
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
}
