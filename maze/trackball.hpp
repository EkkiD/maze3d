#ifndef __TRACKBALL_HPP__
#define __TRACKBALL_HPP__
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/norm.hpp>

class Trackball {
public:
    Trackball (const glm::ivec2 &screen_size):
        m_screenSize(screen_size)
    {
        m_currentQuat = glm::quat();
        m_radius = std::min( (float)screen_size.x / 2, (float)screen_size.y / 2 );
    }

    void mouseDown(const glm::ivec2 &mouse_pos) {
        m_initialMousePos = mouse_pos;
        m_initialQuat = m_currentQuat;
    }

    void mouseMove(const glm::ivec2 &new_pos) {
        glm::vec3 from = projectPoint(m_initialMousePos);
        glm::vec3 to = projectPoint(new_pos);
        
        glm::vec3 axis = glm::cross(from, to);
        m_currentQuat = m_initialQuat * glm::quat(glm::dot(from, to), axis.x, axis.y, axis.z);
        m_currentQuat = glm::normalize(m_currentQuat);
    }

    glm::mat4 rotation() {
        return glm::mat4_cast(m_currentQuat);
    }
private:
    glm::ivec2 m_screenSize;
    glm::ivec2 m_initialMousePos;
    glm::quat m_currentQuat, m_initialQuat;
    float m_radius;

    glm::vec3 projectPoint(const glm::ivec2 &point) {
        glm::vec3 result;
        result.x = (point.x - 0) / (m_radius* 2);
        result.y = (point.y - 0) / (m_radius* 2);
        result.z = 0.0f;

        float mag = glm::length2(result);
        if(mag > 1.0f) {
            result = glm::normalize(result);
        } else {
            result.z = sqrtf(1.0f - mag);
            result = glm::normalize(result);
        }
        return result;
    }

};



#endif
