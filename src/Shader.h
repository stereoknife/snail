//
// Created by kam on 16.6.2024.
//

#ifndef GUITEST_SHADER_H
#define GUITEST_SHADER_H

#include "types.h"

class Shader {
private:
    s32 id;

public:
    explicit Shader (const char* filename);
    Shader          (const char* vtx_filename, const char* frag_filename);

    auto set_float(f32 val) -> void;
    auto set_int(s32 val)   -> void;
    auto set_bool(b1 val)   -> void;
    auto enable()           -> void;
};


#endif //GUITEST_SHADER_H
