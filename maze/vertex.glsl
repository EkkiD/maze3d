# version 330 

// Per-vertex inputs
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Inputs from C++
uniform mat4 MVP; // modelview projection
uniform mat4 V; // view matrix
uniform mat4 M; // model matrix
uniform vec3 LightPos_world; // position of light in worldspace!!!

// to be interpolated per fragment
out vec3 fragmentColor;
out vec3 Position_camera;
out vec3 Normal_camera;
out vec3 EyeDirection_camera;
out vec3 LightDirection_camera;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    fragmentColor = vertexColor;
}
