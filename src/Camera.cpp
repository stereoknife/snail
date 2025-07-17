//
// Created by kam on 17.7.2025.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(vec3 position, vec3 direction) :
    Camera(position, direction, vec3(0.0f, 1.0f, 0.0f))
{}

Camera::Camera(vec3 position, vec3 front, vec3 up) :
    position(position),
    front(front),
    up(up)
{}

auto Camera::view() const -> glm::mat4 {
    return glm::lookAt(position, position + front, up);
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
