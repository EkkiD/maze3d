# version 330 

// Per-vertex inputs
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Inputs from C++
uniform mat4 MVP; // modelview projection
uniform mat4 V; // view matrix
uniform mat4 M; // model matrix
uniform vec3 LightPosition_world; // position of light in worldspace!!!

// to be interpolated per fragment
out vec3 fragmentColor;
out vec3 position_worldspace;
out vec3 Normal_camera;
out vec3 EyeDirection_camera;
out vec3 LightDirection_camera;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

    vec3 vertexPosition_camera = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
    // In camera space, camera is at origin.
    EyeDirection_camera = vec3(0, 0, 0) - vertexPosition_camera;

    // vector from vertex to light, in camera space.
    vec3 lightPosition_camera = (V * vec4(LightPosition_world, 1)).xyz;
    LightDirection_camera = lightPosition_camera + EyeDirection_camera;

    // 
    mat4 invTransM = transpose(inverse(M));
    Normal_camera = (V * invTransM * vec4(vertexNormal_modelspace, 0)).xyz;

    fragmentColor = vertexColor;
}
