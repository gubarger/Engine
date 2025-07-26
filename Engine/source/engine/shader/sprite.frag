#version 410 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D spriteTexture;
uniform vec4 spriteColor = vec4(1.0);

void main() {
    FragColor = texture(spriteTexture, TexCoord) * spriteColor;
}