#include <GL/glew.h>
#include <maze/node.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <maze/viewer.hpp>

void Node::render(glm::mat4 MVP) {
    glBindVertexArray(m_vao);

    auto new_mvp = MVP * m_transform;
    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &new_mvp[0][0]);

    // TODO: unhardcode 30
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(0);
}

void Node::translate(float x, float y, float z) {
    m_transform = m_transform * glm::translate(m_transform, glm::vec3(x, y, z));
}
