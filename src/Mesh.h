//
// Created by kam on 17.6.2024.
//

#ifndef GUITEST_MESH_H
#define GUITEST_MESH_H

#include "types.h"
#include <vector>

/*
struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 tex_coord;
};
*/

class Mesh {
    std::vector<f32> vertices;
    std::vector<u32> indices;
    std::vector<f32> normals;
    std::vector<f32> tex_coords;

    u32 vao;
    u32 vbo_v;
    u32 vbo_i;
    u32 vbo_t;
    u32 vbo_n;

public:
    Mesh();
    Mesh(std::vector<f32> v, std::vector<u32> i, std::vector<f32> t);
    Mesh(std::string filename);

    static auto quad(f32 width, f32 height) -> Mesh;
    static auto cube(f32 side) -> Mesh;

    auto render() const -> void;
    auto set_vertices(std::vector<f32> vertices)    -> void;
    auto set_indices(std::vector<u32> indices)      -> void;
    auto set_tex_coords(std::vector<f32> tex_coords)-> void;
    auto set_normals(std::vector<f32> normals)      -> void;
    auto set_uv(std::vector<f32> uv)                -> void;
    auto update()                                   -> void;

private:
    auto init() -> void;
};


#endif //GUITEST_MESH_H
