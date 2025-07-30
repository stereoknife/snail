#version 330

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 frag_normal;
out vec3 frag_position;

void main(void)  {
    frag_normal = vec3(model * vec4(normal, 0.0));
    frag_position = vec3(model * vec4(vert, 1.0));
    gl_Position = projection * view * model * vec4(vert, 1.0);
}
