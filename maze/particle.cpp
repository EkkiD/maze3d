#include <maze/particle.hpp>
#include <glm/gtc/matrix_transform.hpp>


// XXX Idea:
// What if we put the vertices for all particles into an array, and made a single render call for the full array, rather than 
// doing a separate call for each particle. Interesting.
void Particle::render(glm::mat4 MVP, glm::mat4 M) const {
}

void ParticleGenerator::translate(float x, float y, float z) {
    m_translation = m_translation * glm::translate(m_translation, glm::vec3(x, y, z));
} 
void ParticleGenerator::render(glm::mat4 MVP, glm::mat4 M) const {
    if (!m_running) { return; }
    for (const auto& p: m_particles) {
        p.render(MVP, M);
    }
}

void ParticleGenerator::start() {
    m_running = true;
}

void ParticleGenerator::step() {
    if (!m_running) { return; }

    for (auto& p : m_particles) {
        p.step();
    }
}
