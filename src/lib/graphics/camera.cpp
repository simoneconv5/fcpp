// Copyright © 2020 Giorgio Audrito and Luigi Rapetta. All Rights Reserved.

#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include "lib/graphics/camera.hpp"
#include "lib/graphics/input_types.hpp"

// using namespace fcpp to prevent very verbose code...
using namespace fcpp;


Camera::Camera()
: m_mouseSensitivity{ CAM_DEFAULT_SENSITIVITY },
  m_depth{ CAM_DEFAULT_DEPTH },
  m_depthDefault{ CAM_DEFAULT_DEPTH },
  m_diagonal{ 1000 },
  m_aspectRatio{ 4.0f / 3.0f  },
  m_view{ 1.0f },
  m_viewDefault{ 1.0f },
  m_projection{ 1.0f } {}

void Camera::setViewDefault(glm::vec3 position, float depth, glm::vec3 worldUp, float yaw, float pitch)
{
    // Calculate the front vector
    glm::vec3 calcFront;
    calcFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    calcFront.y = sin(glm::radians(pitch));
    calcFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 front { glm::normalize(calcFront) };

    // Calculate the right
    glm::vec3 right { glm::normalize(glm::cross(front, worldUp)) };  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    
    // Calculate the up
    glm::vec3 up { glm::normalize(glm::cross(right, front)) };
    
    // Calculate view matrix with all the formerly obtained vectors
    m_viewDefault = m_view = glm::lookAt(position, position + front, up);

    // Sets the default depth
    m_depthDefault = m_depth = depth;
    updateProjection();
}

void Camera::applyViewDefault() {
    m_view = m_viewDefault;
    m_depth = m_depthDefault;
    updateProjection();
}

void Camera::setScreen(float width, float height) {
    m_diagonal = std::sqrt(width*width + height*height) / 2;
    m_aspectRatio = (float)width / (float)height;
    updateProjection();
}

void Camera::mouseInput(double x, double y, double xFirst, double yFirst, mouse_type type, int mods)
{
    switch (type) {
        case mouse_type::scroll:
        {
            float new_depth = m_depth * pow(0.98, (mods & GLFW_MOD_SHIFT) > 0 ? y/10 : y);
            m_view = glm::translate(glm::vec3(0.0f, 0.0f, m_depth-new_depth)) * m_view;
            m_depth = new_depth;
            updateProjection();
            break;
        }
        case mouse_type::drag:
            float a = (xFirst*x + yFirst*y) / m_diagonal;
            float b = (xFirst*y - yFirst*x) / m_diagonal;
	        if (std::abs(a) < CAM_THRESHOLD * std::max(std::abs(b), 1.0f)) a = 0;
	        if (std::abs(b) < CAM_THRESHOLD * std::max(std::abs(a), 1.0f)) b = 0;
            a *= m_mouseSensitivity;
            b *= m_mouseSensitivity;
            if ((mods & GLFW_MOD_SHIFT) > 0) {
                a /= 10;
                b /= 10;
            }

            // to add translation with rotation
            m_view =
                glm::translate(glm::normalize(glm::vec3(xFirst, yFirst, 0.0f))*a*m_depth*0.02f) *
		        glm::rotate(glm::radians(-a), glm::vec3{yFirst, -xFirst, 0.0f}) *
		        glm::rotate(glm::radians(b), glm::vec3{0.0f, 0.0f, 1.0f}) * m_view;
            break;
    }
}

void Camera::keyboardInput(int key, bool first, float deltaTime, int mods)
{
    float velocity = m_depth * deltaTime * ((mods & GLFW_MOD_SHIFT) > 0 ? 0.05 : 0.5);
    switch (key) {
        case GLFW_KEY_W:
            m_view = glm::translate(glm::vec3(0.0f, 0.0f, velocity)) * m_view;
            break;
        case GLFW_KEY_S:
            m_view = glm::translate(glm::vec3(0.0f, 0.0f, -velocity)) * m_view;
            break;
        case GLFW_KEY_A:
            m_view = glm::translate(glm::vec3(velocity, 0.0f, 0.0f)) * m_view;
            break;
        case GLFW_KEY_D:
            m_view = glm::translate(glm::vec3(-velocity, 0.0f, 0.0f)) * m_view;
            break;
        case GLFW_KEY_E:
            m_view = glm::translate(glm::vec3(0.0f, -velocity, 0.0f)) * m_view;
            break;
        case GLFW_KEY_Q:
            m_view = glm::translate(glm::vec3(0.0f, velocity, 0.0f)) * m_view;
            break;
    }
}

void Camera::updateProjection() {
    m_projection = glm::perspective(glm::radians(CAM_DEFAULT_FOV), m_aspectRatio, m_depth / 32, m_depth * 32);
}