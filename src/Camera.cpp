//
// Created by kam on 17.7.2025.
//

#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Root.h"

Camera::Camera(vec3 position, vec3 direction) :
    Camera(position, direction, vec3(0.0f, 1.0f, 0.0f))
{}

Camera::Camera(vec3 position, vec3 front, vec3 up) :
    position{position},
    front{front},
    up{up},
    pitch{0},
    yaw{0},
    roll{0},
    fov{45}
{}

auto Camera::view() const -> glm::mat4 {
    return glm::lookAt(-front * 3.f, vec3{0,0,0}, up);
}

auto Camera::projection() const -> glm::mat4 {
    s32 w, h;
    glfwGetWindowSize(Root::window, &w, &h);
    return glm::perspective(glm::radians(fov), static_cast<float>(w) / static_cast<float>(h), 0.1f, 100.0f);

}

auto Camera::move(const vec3 delta) -> void {
    position += delta;
}

auto Camera::set_position(const vec3 position) -> void {
    this->position = position;
}

auto Camera::set_front(const vec3 front) -> void {
    this->front = front;
}

auto Camera::set_up(const vec3 up) -> void {
    this->up = up;
}

auto Camera::set_fov(f32 fov) -> void {
    this->fov = fov;
}

auto Camera::get_fov() const -> f32 {
    return fov;
}


auto Camera::mouse_input(double delta_x, double delta_y) -> void {
    const float sensitivity = 0.1f;

    delta_x *= sensitivity;
    delta_y *= sensitivity;

    yaw += delta_x;
    pitch += delta_y;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    const auto direction = vec3{
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };
    front = glm::normalize(direction);

}
