//
// Created by kam on 16.6.2024.
//

#ifndef GUITEST_SHADER_H
#define GUITEST_SHADER_H

#include <string>

#include "types.h"

class Shader {
    s32 id;
    //const char* name;

public:
    explicit Shader (const char* filename);
    Shader          (const char* vtx_filename, const char* frag_filename);
    Shader          (const std::string& vtx_filename, const std::string &frag_filename);

    auto get_location(const char* name) const         -> s32;

    auto set_float(const char* name, f32 val) const   -> void;
    auto set_int(const char* name, s32 val) const     -> void;
    auto set_bool(const char* name, b1 val) const     -> void;
    auto set_mat4(const char* name, const mat4 &mat) const  -> void;
    auto bind() const                               -> void;
};


#endif //GUITEST_SHADER_H
