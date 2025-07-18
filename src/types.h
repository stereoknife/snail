//
// Created by kam on 16.6.2024.
//

#ifndef GUITEST_TYPES_H
#define GUITEST_TYPES_H

#include "glad/glad.h"
#include <glm/glm.hpp>

using b1 = GLboolean;
using b32 = GLbitfield;

using s8 = GLbyte;
using s16 = GLshort;
using s32 = GLint;
using s64 = GLint64;

using u8 = GLubyte;
using u16 = GLushort;
using u32 = GLuint;
using u64 = GLuint64;

using f16 = GLhalf;
using f32 = GLfloat;
using f64 = GLdouble;

using c32 = GLclampf;
using c64 = GLclampd;

using x32 = GLfixed;

using usize = GLsizei;
using uenum = GLenum;

using ptr = GLintptr;
using ptrsize = GLsizeiptr;

using glsync = GLsync;

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

using mat3 = glm::mat3;
using mat4 = glm::mat4;

#endif //GUITEST_TYPES_H
