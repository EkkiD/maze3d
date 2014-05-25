#ifndef __WALL_HPP__
#define __WALL_HPP__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

enum wall_state {
    initial,
    falling,
    fading,
    removed
};

class Wall {
public:
    void render(glm::mat4 MVP, glm::mat4 M) const;

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

    void knockDown();

    bool isVisible() const { return m_visible; } 
private:
    bool m_visible = true;
    wall_state m_state = initial;

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scaling;
};

#endif
