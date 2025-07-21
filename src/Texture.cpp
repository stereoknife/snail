//
// Created by kam on 30.11.2024.
//

#include <iostream>
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(const Type type) : id{}, type{type} {}

auto Texture::Texture2D(const char *filename) -> Texture {
    Texture tex{Type::Texture2D};
    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    s32 width, height, n_channels;
    u8 *data = stbi_load(filename, &width, &height, &n_channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR::TEXTURE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return tex;
}

auto Texture::Cubemap(const char* path, const char* extension) -> Texture {
    Texture tex{Type::Cubemap};

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex.id);

    s32 width, height, n_channels;

    auto load = [&](const u32 target, const char* file) -> void {
        u8* data = stbi_load(std::format("{}/{}.{}", path, file, extension).c_str(), &width, &height, &n_channels, 3);
        if (data) {
            glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "ERROR::TEXTURE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        stbi_image_free(data);
    };

    load(GL_TEXTURE_CUBE_MAP_POSITIVE_X, "right");
    load(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "left");
    load(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "top");
    load(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "bottom");
    load(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "back");
    load(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "front");

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindTexture(static_cast<s32>(tex.type), 0);

    return tex;
}

auto Texture::set_wrap(Texture::Wrap s, Texture::Wrap t) const -> void {
    glBindTexture(static_cast<s32>(this->type), id);
    glTexParameteri(static_cast<s32>(this->type), GL_TEXTURE_WRAP_S, static_cast<s32>(s));
    glTexParameteri(static_cast<s32>(this->type), GL_TEXTURE_WRAP_T, static_cast<s32>(t));
    glBindTexture(static_cast<s32>(this->type), 0);
}

auto Texture::set_wrap_s(Texture::Wrap s) const -> void {
    glBindTexture(static_cast<s32>(this->type), id);
    glTexParameteri(static_cast<s32>(this->type), GL_TEXTURE_WRAP_S, static_cast<s32>(s));
    glBindTexture(static_cast<s32>(this->type), 0);
}

auto Texture::set_wrap_t(Texture::Wrap t) const -> void {
    glBindTexture(static_cast<s32>(this->type), id);
    glTexParameteri(static_cast<s32>(this->type), GL_TEXTURE_WRAP_T, static_cast<s32>(t));
    glBindTexture(static_cast<s32>(this->type), 0);
}

auto Texture::get_id() const -> u32 {
    return id;
}

auto Texture::bind(s32 buffer) const -> void {
    glActiveTexture(buffer);
    glBindTexture(static_cast<s32>(this->type), this->get_id());
}
