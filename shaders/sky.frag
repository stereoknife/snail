#version 330

out vec4 frag_color;

uniform samplerCube specular_map;

in vec3 tex_coords;

void main (void) {
    frag_color = texture(specular_map, tex_coords);
    float gamma = 2.2;
    //frag_color.rgb = pow(frag_color.rgb, vec3(1.0/gamma));
}
