//
// Created by kam on 30.11.2024.
//

#ifndef REMDERER_TEXTURE_H
#define REMDERER_TEXTURE_H

#include "types.h"

class Texture {
public:
    enum class Wrap : s32 {
        Repeat = GL_REPEAT,
        Mirror = GL_MIRRORED_REPEAT,
        Clamp = GL_CLAMP_TO_EDGE,
        Border = GL_CLAMP_TO_BORDER
    };

private:
    u32 id;

public:
    explicit Texture (const char* filename);

    auto set_wrap(Wrap s, Wrap t) const -> void;
    auto set_wrap_s(Wrap s) const       -> void;
    auto set_wrap_t(Wrap t) const       -> void;

    auto get_id()                       -> s32;
};


#endif //REMDERER_TEXTURE_H
