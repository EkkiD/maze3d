# version 330 

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP; // modelview projection


void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}
