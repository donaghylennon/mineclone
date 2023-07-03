#version 330 core

in vec2 texture_coords;

out vec4 frag_color;

uniform sampler2D texture0;
uniform float highlight;

void main() {
    frag_color = mix(texture(texture0, texture_coords), vec4(1.0, 1.0, 1.0, 1.0), highlight);
}
