#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Particle {
public:
    void render(glm::mat4 MVP, glm::mat4 M) const;
    void step() {};

private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;
};

class ParticleGenerator {
public:
    ParticleGenerator(): m_running(false) {}

    void translate(float x, float y, float z);

    void start();

    void step();
    void render(glm::mat4 MVP, glm::mat4 M) const;
    
private:
    std::vector<Particle> m_particles = std::vector<Particle>(100);
    glm::mat4 m_translation;
    bool m_running;
};

#endif
