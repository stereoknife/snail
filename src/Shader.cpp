//
// Created by kam on 16.6.2024.
//

#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *filename) :
    Shader(std::string(filename) + ".vert", std::string(filename) + ".frag") {}

Shader::Shader(const char *vtx_filename, const char *frag_filename) {
    std::string vtx_str;
    std::string frag_str;
    std::ifstream vtx_file;
    std::ifstream frag_file;

    vtx_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vtx_file.open(vtx_filename);
        std::stringstream vtx_stream;
        vtx_stream << vtx_file.rdbuf();
        vtx_file.close();

        frag_file.open(frag_filename);
        std::stringstream frag_stream;
        frag_stream << frag_file.rdbuf();
        frag_file.close();

        vtx_str = vtx_stream.str();
        frag_str = frag_stream.str();
    }
    catch(std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    u32 vtx, frag;

    const char* vtx_src = vtx_str.c_str();
    const char* frag_src = frag_str.c_str();

    s32 success;
    char log[512];

    vtx = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtx, 1, &vtx_src, nullptr);
    glCompileShader(vtx);

    glGetShaderiv(vtx, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vtx, 512, nullptr, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    }

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &frag_src, nullptr);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(frag, 512, nullptr, log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vtx);
    glAttachShader(id, frag);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    }

    glDeleteShader(vtx);
    glDeleteShader(frag);
}

Shader::Shader(const std::string& vtx_filename, const std::string &frag_filename) :
    Shader(vtx_filename.c_str(), frag_filename.c_str()) {}

// Getter
auto Shader::get_location(const char *name) const -> s32 {
    return glGetUniformLocation(id, name);
}

// Setter
auto Shader::set_float(const char* name, const f32 val) const -> void {
    glUniform1f(glGetUniformLocation(id, name), val);
}

auto Shader::set_int(const char* name, const s32 val) const -> void {
    glUniform1i(glGetUniformLocation(id, name), val);
}

auto Shader::set_bool(const char* name, const b1 val) const -> void {
    glUniform1i(glGetUniformLocation(id, name), static_cast<s32>(val));
}

auto Shader::enable() const -> void {
    glUseProgram(id);
}
