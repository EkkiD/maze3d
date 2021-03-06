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

void Wall::rotate(float radians, glm::vec3 axis) {
    m_rotation = m_rotation * glm::rotate(m_rotation, radians, axis);
}

void Wall::render(glm::mat4 MVP, glm::mat4 M, glm::mat4 V, glm::mat4 invtransvm) const {
    glBindVertexArray(G_CUBE_VAO);

    auto new_mvp = MVP * m_translation * m_rotation * m_scaling;
    auto new_m = M * m_translation * m_rotation * m_scaling ;
    auto new_invtransvm = glm::inverse(glm::transpose(V * new_m));

    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &new_mvp[0][0]);
    glUniformMatrix4fv(G_M_ID, 1, GL_FALSE, &new_m[0][0]);
    glUniformMatrix4fv(G_INVTRANSVM_ID, 1, GL_FALSE, &new_invtransvm[0][0]);
    glUniform1f(G_ALPHA_ID, m_alpha);

    // TODO: unhardcode 30
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(G_M_ID, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(G_INVTRANSVM_ID, 1, GL_FALSE, &invtransvm[0][0]);
    glUniform1f(G_ALPHA_ID, 1.0);

    glBindVertexArray(0);
}

void Wall::step() {
    if (m_state == falling) {
        m_angle = m_angle - m_rotation_velocity;
        m_angle = m_angle < 0.0f ? 0.0f : m_angle;

        m_rotation_velocity = 0.24 * sqrt(3*9.81*(1-std::sin(m_angle)));

        // Depending on the direction of the wall, we want to fall in a different direction;
        m_rotation = glm::rotate(glm::mat4(1.0f), float(0.5 * PI - m_angle), m_rotation_axis);
        
        if (m_angle <= 0.0f) {
            m_angle = 0.0f;
            m_state = fading;
        }
    } else if (m_state == fading) {
        m_alpha -= fade_step; 
        if (m_alpha < 0) {
            m_state = removed;
        }
    }

    m_particle.step();
}

void Wall::knockDown(int direction) {
    m_state = falling;
    m_rotation_velocity = 0.001f;

    switch (direction) {
        case NORTH:
            m_rotation_axis = glm::vec3(-1.0f, 0.0f, 0.0f);
            break;
        case SOUTH:
            m_rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f);
            break;
        case EAST:
            m_rotation_axis = glm::vec3(0.0f, 0.0f, -1.0f);
            break;
        case WEST:
            m_rotation_axis = glm::vec3(0.0f, 0.0f, 1.0f);
            break;
    }

    m_particle.start();
}
