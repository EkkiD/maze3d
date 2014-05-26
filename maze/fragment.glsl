#version 330 core

in vec3 fragmentColor;
in vec3 position_worldspace;
in vec3 position_base;
in vec3 Normal_camera;
in vec3 EyeDirection_camera;
in vec3 LightDirection_camera;

// Output
out vec4 color;

// From C++
uniform vec3 LightPosition_world;
uniform float ALPHA; // The alpha value to use


vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
     return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v)
  { 
  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

// First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;

// Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );

  //   x0 = x0 - 0.0 + 0.0 * C.xxx;
  //   x1 = x0 - i1  + 1.0 * C.xxx;
  //   x2 = x0 - i2  + 2.0 * C.xxx;
  //   x3 = x0 - 1.0 + 3.0 * C.xxx;
  vec3 x1 = x0 - i1 + C.xxx;
  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y

// Permutations
  i = mod289(i); 
  vec4 p = permute( permute( permute( 
             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
           + i.y + vec4(0.0, i1.y, i2.y, 1.0 )) 
           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

// Gradients: 7x7 points over a square, mapped onto an octahedron.
// The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
  float n_ = 0.142857142857; // 1.0/7.0
  vec3  ns = n_ * D.wyz - D.xzx;

  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)

  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);

  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );

  //vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
  //vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));

  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);

//Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;

// Mix final noise value
  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
                                dot(p2,x2), dot(p3,x3) ) );
  }

float turbulence(vec3 point) {
    float sum = 0;
    sum += snoise(point) +
           0.5 * snoise(2 * point) +
           0.25 * snoise(4 * point) +
           0.125 * snoise(8 * point) + 
           0.0625 * snoise(16 * point);
    return abs(sum);
}

void main() {
    // TODO: move to C++ 
    vec3 LightColor = vec3(1, 1, 1);
    float LightPower = 400.0f;

    // Material properties
    vec3 MaterialDiffuseColor = vec3(0.6, 0.6, 0.66); //fragmentColor;
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

    color = vec4(MaterialAmbientColor + 
            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance2) +
            MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance2),
            ALPHA);

    vec3 pose = vec3(0.1 * (position_worldspace.x + 5), position_worldspace.y, 0.1 * (position_worldspace.z + 5));
    vec3 noise_pos = 15 * pose;
    float noise_base =  7 * (position_worldspace.x + position_worldspace.z +  0.2 * position_worldspace.y);
    float noise_val = sin(noise_base + 2.5 * (turbulence(position_worldspace)));
    noise_val = 1 - noise_val;

    color = noise_val * color;
    color.a = ALPHA;
}
