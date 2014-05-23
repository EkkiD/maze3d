#include <maze/wall.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <maze/opengl.hpp>
#include <maze/viewer.hpp>

void Wall::translate(float x, float y, float z) {
    m_translation = m_translation * glm::translate(m_translation, glm::vec3(x, y, z));
}

void Wall::scale(float x, float y, float z) {
    m_scaling = m_scaling * glm::scale(m_scaling, glm::vec3(x, y, z));
}

void Wall::render(glm::mat4 MVP, glm::mat4 M) const {
    glBindVertexArray(G_CUBE_VAO);

    auto new_mvp = MVP * m_translation * m_scaling;
    auto new_m = M * m_translation * m_scaling;
    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &new_mvp[0][0]);
    glUniformMatrix4fv(G_M_ID, 1, GL_FALSE, &new_m[0][0]);

    // TODO: unhardcode 30
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(G_M_ID, 1, GL_FALSE, &M[0][0]);
    glBindVertexArray(0);
}

void Wall::knockDown() {
    m_visible = false;
}
