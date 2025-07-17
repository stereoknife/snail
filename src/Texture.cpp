//
// Created by kam on 30.11.2024.
//

#include <iostream>
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(const char *filename) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

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
}

auto Texture::set_wrap(Texture::Wrap s, Texture::Wrap t) const -> void {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (s32)s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (s32)t);
    glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::set_wrap_s(Texture::Wrap s) const -> void {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (s32)s);
    glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::set_wrap_t(Texture::Wrap t) const -> void {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (s32)t);
    glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::get_id() -> s32 {
    return id;
}
