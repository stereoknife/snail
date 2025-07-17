#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D boundTexture;

void main()
{
    FragColor = texture(boundTexture, TexCoord);
    //FragColor = vec4(TexCoord.r, TexCoord.g, 0.0, 1.0);
}