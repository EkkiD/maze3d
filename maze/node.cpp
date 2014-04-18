#include <GL/glew.h>
#include <maze/node.hpp>

void Node::render(glm::mat4 MVP) {
    glBindVertexArray(m_vao);
    // TODO: unhardcode 30
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
}
