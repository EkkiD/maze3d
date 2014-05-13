#ifndef __INTERACTION_HPP__
#define __INTERACTION_HPP__
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <maze/trackball.hpp>

class Interaction{
public:
    void init(GLFWwindow* window) {
        glfwSetMouseButtonCallback(window, onMouseButton);
        glfwSetCursorPosCallback(window, onMouseMove);
        glfwSetWindowUserPointer(window, (void*)this);
    }

    static void onMouseButton(GLFWwindow* window, int button, int action, int mods){
        auto self = static_cast<Interaction*>(glfwGetWindowUserPointer(window));
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            if (action == GLFW_PRESS) {
                self->m_trackball.mouseDown(glm::ivec2((int)x, (int)y));
            } else {
                self->m_rotation = self->m_rotation * self->m_trackball.rotation();
                self->m_trackball.reset();
            }
        }
        self->m_mouseDown = (action == GLFW_PRESS);
        self->m_mouseButton = button;
        self->m_mousePos = glm::vec2(x, y);
    }

    static void onMouseMove(GLFWwindow* window, double x, double y){
        auto self = static_cast<Interaction*>(glfwGetWindowUserPointer(window));
        y = WINDOW_Y - y;
        if (!self->m_mouseDown) { return; }
        if (self->m_mouseButton == GLFW_MOUSE_BUTTON_MIDDLE) {
            self->m_trackball.mouseMove(glm::ivec2((int)x, (int)y));
        } else if (self->m_mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
            float dx = x - self->m_mousePos.x;
            float dy = y - self->m_mousePos.y;
            self->translate(dx / 60.0f, dy / 60.0f, 0.0f);
        }
        self->m_mousePos = glm::vec2(x, y);
    }

    const glm::vec3 cameraLoc() { return m_cameraLoc; }

    glm::mat4 rotation() { 
        return m_rotation * m_trackball.rotation(); 
    }
    glm::mat4 translation() { return glm::translate(glm::mat4(1.0f), m_translation); }


private:
    void translate(float x, float y, float z) {
        m_translation = m_translation + glm::vec3(x, y , z);
    }

    Trackball m_trackball = Trackball(glm::ivec2(WINDOW_X, WINDOW_Y));
    glm::vec2 m_mousePos;
    glm::vec3 m_cameraLoc = glm::vec3(11.0f, 11.0f, 11.0f);
    glm::vec3 m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 m_rotation = glm::mat4(1.0f);
    bool m_mouseDown;
    int m_mouseButton;
};
#endif
