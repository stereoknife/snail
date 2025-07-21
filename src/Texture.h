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

    enum class Type {
        Texture2D = GL_TEXTURE_2D,
        Cubemap = GL_TEXTURE_CUBE_MAP
    };

private:
    u32 id;
    Type type;

    explicit Texture (Type type);

public:
    //Texture(Type type, const char* filename);
    static auto Texture2D(const char* filename) -> Texture;
    static auto Cubemap(const char* path, const char* extension) -> Texture;

    auto set_wrap(Wrap s, Wrap t) const -> void;
    auto set_wrap_s(Wrap s) const       -> void;
    auto set_wrap_t(Wrap t) const       -> void;

    auto get_id() const                 -> u32;

    auto bind(s32 target) const -> void;
};


#endif //REMDERER_TEXTURE_H
