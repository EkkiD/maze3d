#ifndef __WALL_HPP__
#define __WALL_HPP__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <maze/common.hpp>
#include <maze/particle.hpp>


enum wall_state {
    initial,
    falling,
    fading,
    removed
};

class Wall {
public:
    void render(glm::mat4 MVP, glm::mat4 M) const;
    void step();

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float radians, glm::vec3 axis);

    void knockDown(int direction);

    bool isVisible() const { return m_state != removed; } 

private:
    wall_state m_state = initial;
    float m_angle = 0.5f * PI;
    float m_rotation_velocity = 0.0f;
    glm::vec3 m_rotation_axis;

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scaling;
    float m_alpha = 1.0;

    ParticleGenerator m_particle;

    constexpr static const float fade_step = 1.0f / 60; 
};

#endif
