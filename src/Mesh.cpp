//
// Created by kam on 17.6.2024.
//

#include "Mesh.h"

#include <utility>

Mesh::Mesh(std::vector<f32> v, std::vector<s32> i) :
    vao{},
    vbo_v{},
    vbo_i{},
    vertices{std::move(v)},
    indices{std::move(i)}
{
    init();
}

auto Mesh::quad(f32 width, f32 height) -> Mesh {
    f32 hw = width / 2;
    f32 hh = height / 2;
    return Mesh {
        std::vector<f32> {
            -hw, -hh, 0.f,
             hw, -hh, 0.f,
             hw,  hh, 0.f,
            -hw,  hh, 0.f
        },
        std::vector<s32> {
            0, 1, 2,
            2, 3, 0
        }
    };
}

auto Mesh::cube(f32 side) -> Mesh {
    f32 hs = side / 2;
    return Mesh {
        std::vector<f32>{
                -hs, -hs, -hs, // 0 - L B F
                -hs, -hs,  hs, // 1 - L B K
                -hs,  hs, -hs, // 2 - L T F
                -hs,  hs,  hs, // 3 - L T K
                 hs, -hs, -hs, // 4 - R B F
                 hs, -hs,  hs, // 5 - R B K
                 hs,  hs, -hs, // 6 - R T F
                 hs,  hs,  hs, // 7 - R T K
        },
        // (-1,  1) o----o ( 1, 1)
        //          | .´ |
        // (-1, -1) o----o ( 1,-1)
        std::vector<s32>{
                // Bottom face
                0, 1, 5,
                5, 4, 0,
                // Front face
                0, 2, 6,
                6, 4, 0,
                // Left face
                0, 1, 3,
                3, 2, 0,
                // Back face
                1, 3, 6,
                6, 5, 1,
                // Right face
                4, 5, 7,
                7, 6, 4,
                // Top face
                2, 3, 7,
                7, 6, 2
        }
    };
}

auto Mesh::render() -> void {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

auto Mesh::init() -> void {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo_v);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
    glBufferData(GL_ARRAY_BUFFER, (s32)(vertices.size() * sizeof(f32)), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_i);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (s32)(indices.size() * sizeof(s32)), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}
