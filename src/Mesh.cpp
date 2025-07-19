//
// Created by kam on 17.6.2024.
//

#include "Mesh.h"

#include <filesystem>
#include <iostream>
#include <utility>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh() :
    vertices{},
    indices{},
    normals{},
    tex_coords{},
    vao{},
    vbo_v{},
    vbo_i{},
    vbo_t{},
    vbo_n{}
{
    init();
}

Mesh::Mesh(std::vector<f32> v, std::vector<u32> i, std::vector<f32> t) :
    vertices{std::move(v)},
    indices{std::move(i)},
    normals{},
    tex_coords{std::move(t)},
    vao{},
    vbo_v{},
    vbo_i{},
    vbo_t{},
    vbo_n{}
{
    init();
    update();
}

Mesh::Mesh(const char* filename) : Mesh() {
    Assimp::Importer import;
    const aiScene* scn = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);

    if(!scn || scn->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scn->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    aiNode* n = scn->mRootNode;

    if (n->mNumMeshes > 1) std::cout << "WARNING::ASSIMP::Only one mesh allowed to be imported" << std::endl;

    aiMesh* m = scn->mMeshes[0];

    this->vertices.reserve(m->mNumVertices * 3);
    this->normals.reserve(m->mNumVertices * 3);
    this->tex_coords.reserve(m->mNumVertices * 2);
    this->indices.reserve(m->mNumFaces * 3);

    for (int i = 0; i < m->mNumVertices; ++i) {
        vertices.push_back(m->mVertices[i].x);
        vertices.push_back(m->mVertices[i].y);
        vertices.push_back(m->mVertices[i].z);
        normals.push_back(m->mNormals[i].x);
        normals.push_back(m->mNormals[i].y);
        normals.push_back(m->mNormals[i].z);

        if (m->mTextureCoords[0]) {
            tex_coords.push_back(m->mTextureCoords[0][i].x);
            tex_coords.push_back(m->mTextureCoords[0][i].y);
        } else {
            tex_coords.push_back(0);
            tex_coords.push_back(0);
        }
    }

    for (int i = 0; i < m->mNumFaces; ++i) {
        aiFace f = m->mFaces[i];
        for (int j = 0; j < f.mNumIndices; ++j) {
            indices.push_back(f.mIndices[j]);
        }
    }

    init();
    update();
}

Mesh::Mesh(const std::string& filename) : Mesh(filename.c_str()) {}

auto Mesh::quad(f32 width, f32 height) -> Mesh {
    f32 hw = width / 2;
    f32 hh = height / 2;
    return Mesh {
        std::vector {
            -hw, -hh, 0.f,
             hw, -hh, 0.f,
             hw,  hh, 0.f,
            -hw,  hh, 0.f
        },
        std::vector<u32> {
            0, 1, 2,
            2, 3, 0
        },
        std::vector {
            0.f, 0.f,
            1.f, 0.f,
            1.f, 1.f,
            0.f, 1.f
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
        std::vector<u32>{
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
                1, 3, 7,
                7, 5, 1,
                // Right face
                4, 5, 7,
                7, 6, 4,
                // Top face
                2, 3, 7,
                7, 6, 2
        },
        std::vector<f32> {
                0.f, 0.f,
                1.f, 0.f,
                1.f, 1.f,
                0.f, 1.f
        }
    };
}

auto Mesh::render() const -> void {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (s32)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

auto Mesh::set_vertices(std::vector<f32> vertices) -> void {
    this->vertices = std::move(vertices);
}

auto Mesh::set_indices(std::vector<u32> indices) -> void {
    this->indices = std::move(indices);
}

auto Mesh::set_tex_coords(std::vector<f32> tex_coords) -> void {
    this->tex_coords = std::move(tex_coords);
}

auto Mesh::set_normals(std::vector<f32> normals) -> void {
    this->normals = std::move(normals);
}

auto Mesh::init() -> void {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo_v);
    glGenBuffers(1, &vbo_t);
    glGenBuffers(1, &vbo_i);
    glGenBuffers(1, &vbo_n);

    glBindVertexArray(0);
}

auto Mesh::set_uv(std::vector<f32> uv) -> void {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_t);
    glBufferData(GL_ARRAY_BUFFER, (s32)(uv.size() * sizeof(f32)), &uv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), (void*)nullptr);
}

auto Mesh::update() -> void {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
    glBufferData(GL_ARRAY_BUFFER, (s32)(vertices.size() * sizeof(f32)), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_t);
    glBufferData(GL_ARRAY_BUFFER, (s32)(tex_coords.size() * sizeof(f32)), &tex_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (s32)(indices.size() * sizeof(s32)), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}
