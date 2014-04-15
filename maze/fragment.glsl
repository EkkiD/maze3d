#version 330 core

in vec3 fragmentColor;

// Output
out vec3 color;

void main() {
    //already been interpolated
    color = fragmentColor;
}
