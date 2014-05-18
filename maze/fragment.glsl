#version 330 core

in vec3 fragmentColor;
in vec3 position_worldspace;
in vec3 position_base;
in vec3 Normal_camera;
in vec3 EyeDirection_camera;
in vec3 LightDirection_camera;

// Output
out vec3 color;

// From C++
uniform sampler1D permTex;
uniform sampler1D gradTex;
uniform vec3 LightPosition_world;


/*
 * To create offsets of one texel and one half texel in the
 * texture lookup, we need to know the texture image size.
 */
#define ONE 0.00390625
#define ONEHALF 0.001953125
// The numbers above are 1/256 and 0.5/256, change accordingly
// if you change the code to use another texture size.

float fade(float t)
{
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

float perm (float x)
{
    return texture1D(permTex, x).a;
}

float grad(float x, vec3 p)
{
    return dot(texture1D(gradTex, x).rgb * 4.0 - 1.0, p);
}

float lerp(float t, float a, float b)
{
    return a + t * (b-a);
}

float noise(vec3 p)
{
  vec3 Pi = ONE*floor(p)+ONEHALF; // Integer part, scaled so +1 moves one texel
                                  // and offset 1/2 texel to sample texel centers
  vec3 Pf = fract(p);     // Fractional part for interpolation

  float u = fade(Pf.x);
  float v = fade(Pf.y);
  float w = fade(Pf.z);

  float A = perm(Pi.x) + Pi.y;
  float AA = perm(A) + Pi.z;
  float AB = perm(A+ONE) + Pi.z;

  float B = perm(Pi.x + ONE) + Pi.y;
  float BA = perm(B) + Pi.z;
  float BB = perm(B+ONE) + Pi.z;

  return lerp(w, lerp(v, lerp(u, grad(perm(AA), Pf), 
                                grad(perm(BA), Pf + vec3(-1.0, 0.0, 0.0))), 
                        lerp(u, grad(perm(AB), Pf + vec3(0.0, -1.0, 0.0)),
                                grad(perm(BB), Pf + vec3(-1.0, -1.0, 0.0)))),
                lerp(v, lerp(u, grad(perm(AA+ONE), Pf + vec3(0.0, 0.0, -1.0)), 
                                grad(perm(BA+ONE), Pf + vec3(-1.0, 0.0, -1.0))), 
                        lerp(u, grad(perm(AB+ONE), Pf + vec3(0.0, -1.0, -1.0)),
                                grad(perm(BB+ONE), Pf + vec3(-1.0, -1.0, -1.0)))));
}

void main() {
    // TODO: move to C++ 
    vec3 LightColor = vec3(1, 1, 1);
    float LightPower = 400.0f;

    // Material properties
    vec3 MaterialDiffuseColor = fragmentColor;
    vec3 MaterialAmbientColor = vec3(0.2, 0.2, 0.2) * MaterialDiffuseColor;
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

//    color = MaterialAmbientColor + 
//            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance2) +
//            MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance2);
//    color = 0.2 * position_worldspace;
//    color.g = 0.6 * position_worldspace.y;

    float noise_val = sin( position_base.x + 4*mod(position_base.x, 4)+ 
            1.5*( 2*abs(noise(position_base)) + 
                0.5* abs(noise(2*position_base)) + 
                0.25 * abs(noise(4*position_base)) +
                0.125 * abs(noise(8*position_base))));
    noise_val = noise_val * noise_val * noise_val;

    color = noise_val * MaterialDiffuseColor;
}
