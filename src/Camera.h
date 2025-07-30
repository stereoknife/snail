//
// Created by kam on 17.7.2025.
//
#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

class Camera {
    vec3 position, front, up;
    f32 pitch, yaw, roll, fov;

public:
    Camera(vec3 position, vec3 front);
    Camera(vec3 position, vec3 front, vec3 up);

    auto view() const                   -> glm::mat4;
    auto projection() const             -> glm::mat4;

    auto move(vec3 delta)               -> void;

    auto set_position(vec3 position)    -> void;
    auto set_front(vec3 front)          -> void;
    auto set_up(vec3 up)                -> void;
    auto set_fov(f32 fov)               -> void;

    auto get_fov() const                -> f32;

    auto mouse_input(double x_pos, double y_pos) -> void;
};



#endif //CAMERA_H
