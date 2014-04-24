#version 330 core

in vec3 fragmentColor;
in vec3 position_worldspace;
in vec3 Normal_camera;
in vec3 EyeDirection_camera;
in vec3 LightDirection_camera;


// Output
out vec3 color;

// 
uniform vec3 LightPosition_world;

void main() {
    // TODO: move to C++ 
    vec3 LightColor = vec3(1, 1, 1);
    float LightPower = 50.0f;

    // Material properties
    vec3 MaterialDiffuseColor = fragmentColor;
    vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

    //distance to light
    float distance  = length(LightPosition_world - position_worldspace);
    float distance2 = distance * distance;

    vec3 n = normalize(Normal_camera);
    // direction from fragment to light
    vec3 l = normalize(LightDirection_camera);

    // cosine angle between normal and the light direction
    float cosTheta = clamp(dot(n, l), 0,1);

    // vector towards camera
    vec3 E  = normalize(EyeDirection_camera);
    // direction of reflection
    vec3 R  = reflect(-l, n);
    // cosine angle between eye vector and reflection vector
    float cosAlpha = clamp( dot(E, R), 0, 1);

    color = MaterialAmbientColor + 
            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance2) + 0;
            //MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance2);
}
