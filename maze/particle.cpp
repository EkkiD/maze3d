#include <maze/particle.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Particle::render(glm::mat4 MVP, glm::mat4 M) const {
}

void ParticleGenerator::translate(float x, float y, float z) {
    m_translation = m_translation * glm::translate(m_translation, glm::vec3(x, y, z));
}

void ParticleGenerator::render(glm::mat4 MVP, glm::mat4 M) const {
    for (const auto& p: m_particles) {
        p.render(MVP, M);
    }
}
