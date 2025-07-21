#version 330

out vec4 frag_color;

in vec3 frag_normal;
in vec3 frag_position;

uniform mat4 view;
uniform vec3 light;

void main (void) {
    // Parameters
    float ambient_strength = 0.1;
    float specular_strength = 0.5;
    vec3 light_color = vec3(1.0, 1.0, 0.0);
    vec3 object_color = vec3(1.0, 0.0, 1.0);

    // Calc
    vec3 light_dir = normalize(light - frag_position);
    vec3 view_position = inverse(view)[3].xyz;
    vec3 view_dir = normalize(view_position - frag_position);
    vec3 reflect_dir = reflect(-light_dir, frag_normal);

    // Ambient
    vec3 ambient = ambient_strength * light_color;

    // Diffuse
    float diff = max(dot(frag_normal, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    // Specular
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = spec * light_color;

    vec3 result = (specular + ambient + diffuse) * object_color;

    float gamma = 2.2;
    result = pow(result, vec3(1.0/gamma));

    frag_color = vec4(result, 1.0);
    //frag_color = vec4(view_dir, 1.0);
}
