//
// Created by kam on 16.6.2024.
//

#ifndef GUITEST_SHADER_H
#define GUITEST_SHADER_H

#include "types.h"

class Shader {
    s32 id;

public:
    explicit Shader (const char* filename);
    Shader          (const char* vtx_filename, const char* frag_filename);

    auto get_location(const char* name)         -> s32;

    auto set_float(const char* name, f32 val)   -> void;
    auto set_int(const char* name, s32 val)     -> void;
    auto set_bool(const char* name, b1 val)     -> void;
    auto enable()                               -> void;
};


#endif //GUITEST_SHADER_H
