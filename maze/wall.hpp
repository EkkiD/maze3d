#ifndef __WALL_HPP__
#define __WALL_HPP__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>


class Wall {
public:
    void render(glm::mat4 MVP) const;

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

private:
    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scaling;
};

#endif
