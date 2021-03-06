#ifndef MAZESHADERS_HPP
#define MAZESHADERS_HPP

const char* const MAZEVERTEXSHADER = "// Per-vertex inputs \n\n"
"attribute vec3 vertexPosition_modelspace;\n"
"attribute vec3 vertexColor;\n"
"attribute vec3 vertexNormal_modelspace;\n"
"\n"
"// Inputs from C++\n"
"uniform mediump mat4 MVP; // modelview projection\n"
"uniform mediump mat4 V; // view matrix\n"
"uniform mediump mat4 M; // model matrix\n"
"uniform mediump mat4 INVTRANSVM; // invtrans matrix\n"
"uniform mediump vec3 LightPosition_world; // position of light in worldspace!!!\n"
"\n"
"// to be interpolated per fragment\n"
"varying mediump vec3 fragmentColor;\n"
"varying mediump vec3 position_worldspace;\n"
"varying mediump vec3 position_base;\n"
"varying mediump vec3 Normal_camera;\n"
"varying mediump vec3 EyeDirection_camera;\n"
"varying mediump vec3 LightDirection_camera;\n"
"\n"
"void main() {\n"
"    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n"
"    position_base = (vec4(vertexPosition_modelspace, 1)).xyz;\n"
"\n"
"    position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;\n"
"\n"
"    vec3 vertexPosition_camera = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;\n"
"\n"
"    // In camera space, camera is at origin.\n"
"    EyeDirection_camera = vec3(0, 0, 0) - vertexPosition_camera;\n"
"\n"
"    // vector from vertex to light, in camera space.\n"
"    vec3 lightPosition_camera = (V * vec4(LightPosition_world, 1)).xyz;\n"
"    LightDirection_camera = lightPosition_camera + EyeDirection_camera;\n"
"\n"
"    // \n"
"    Normal_camera = (INVTRANSVM * vec4(vertexNormal_modelspace, 0)).xyz;\n"
"\n"
"    fragmentColor = vertexColor;\n"
"}\n"
"";

const char* const MAZEFRAGMENTSHADER = 
"\n"
"varying mediump vec3 fragmentColor;\n"
"varying mediump vec3 position_worldspace;\n"
"varying mediump vec3 position_base;\n"
"varying mediump vec3 Normal_camera;\n"
"varying mediump vec3 EyeDirection_camera;\n"
"varying mediump vec3 LightDirection_camera;\n"
"\n"
"// From C++\n"
"uniform mediump vec3 LightPosition_world;\n"
"uniform mediump float ALPHA; // The alpha value to use\n"
"\n"
"\n"
"mediump vec3 mod289(mediump vec3 x) {\n"
"  return x - floor(x * (1.0 / 289.0)) * 289.0;\n"
"}\n"
"\n"
"mediump vec4 mod289(mediump vec4 x) {\n"
"  return x - floor(x * (1.0 / 289.0)) * 289.0;\n"
"}\n"
"\n"
"mediump vec4 permute(mediump vec4 x) {\n"
"     return mod289(((x*34.0)+1.0)*x);\n"
"}\n"
"\n"
"mediump vec4 taylorInvSqrt(mediump vec4 r)\n"
"{\n"
"  return 1.79284291400159 - 0.85373472095314 * r;\n"
"}\n"
"\n"
"mediump float snoise(mediump vec3 v)\n"
"  { \n"
"  mediump vec2  C = vec2(1.0/6.0, 1.0/3.0) ;\n"
"  mediump vec4  D = vec4(0.0, 0.5, 1.0, 2.0);\n"
"\n"
"// First corner\n"
"  mediump vec3 i  = floor(v + dot(v, C.yyy) );\n"
"  mediump vec3 x0 =   v - i + dot(i, C.xxx) ;\n"
"\n"
"// Other corners\n"
"  mediump vec3 g = step(x0.yzx, x0.xyz);\n"
"  mediump vec3 l = 1.0 - g;\n"
"  mediump vec3 i1 = min( g.xyz, l.zxy );\n"
"  mediump vec3 i2 = max( g.xyz, l.zxy );\n"
"\n"
"  //   x0 = x0 - 0.0 + 0.0 * C.xxx;\n"
"  //   x1 = x0 - i1  + 1.0 * C.xxx;\n"
"  //   x2 = x0 - i2  + 2.0 * C.xxx;\n"
"  //   x3 = x0 - 1.0 + 3.0 * C.xxx;\n"
"  mediump vec3 x1 = x0 - i1 + C.xxx;\n"
"  mediump vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y\n"
"  mediump vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y\n"
"\n"
"// Permutations\n"
"  i = mod289(i); \n"
"  mediump vec4 p = permute( permute( permute( \n"
"             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))\n"
"           + i.y + vec4(0.0, i1.y, i2.y, 1.0 )) \n"
"           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));\n"
"\n"
"// Gradients: 7x7 points over a square, mapped onto an octahedron.\n"
"// The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)\n"
"  mediump float n_ = 0.142857142857; // 1.0/7.0\n"
"  mediump vec3  ns = n_ * D.wyz - D.xzx;\n"
"\n"
"  mediump vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)\n"
"\n"
"  mediump vec4 x_ = floor(j * ns.z);\n"
"  mediump vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)\n"
"\n"
"  mediump vec4 x = x_ *ns.x + ns.yyyy;\n"
"  mediump vec4 y = y_ *ns.x + ns.yyyy;\n"
"  mediump vec4 h = 1.0 - abs(x) - abs(y);\n"
"\n"
"  mediump vec4 b0 = vec4( x.xy, y.xy );\n"
"  mediump vec4 b1 = vec4( x.zw, y.zw );\n"
"\n"
"  //mediump vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;\n"
"  //mediump vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;\n"
"  mediump vec4 s0 = floor(b0)*2.0 + 1.0;\n"
"  mediump vec4 s1 = floor(b1)*2.0 + 1.0;\n"
"  mediump vec4 sh = -step(h, vec4(0.0));\n"
"\n"
"  mediump vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;\n"
"  mediump vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;\n"
"\n"
"  mediump vec3 p0 = vec3(a0.xy,h.x);\n"
"  mediump vec3 p1 = vec3(a0.zw,h.y);\n"
"  mediump vec3 p2 = vec3(a1.xy,h.z);\n"
"  mediump vec3 p3 = vec3(a1.zw,h.w);\n"
"\n"
"//Normalise gradients\n"
"  mediump vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));\n"
"  p0 *= norm.x;\n"
"  p1 *= norm.y;\n"
"  p2 *= norm.z;\n"
"  p3 *= norm.w;\n"
"\n"
"// Mix final noise value\n"
"  mediump vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);\n"
"  m = m * m;\n"
"  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), \n"
"                                dot(p2,x2), dot(p3,x3) ) );\n"
"  }\n"
"\n"
"mediump float turbulence(mediump vec3 point) {\n"
"    mediump float sum = 0.0;\n"
"    sum += snoise(point) +\n"
"           0.5 * snoise(2.0 * point) +\n"
"           0.25 * snoise(4.0 * point) +\n"
"           0.125 * snoise(8.0 * point) + \n"
"           0.0625 * snoise(16.0 * point);\n"
"    return abs(sum);\n"
"}\n"
"\n"
"void main() {\n"
"    // TODO: move to C++ \n"
"    mediump vec3 LightColor = vec3(1, 1, 1);\n"
"    mediump float LightPower = 400.0;\n"
"\n"
"    // Material properties\n"
"    mediump vec3 MaterialDiffuseColor = vec3(0.6, 0.6, 0.66); //fragmentColor;\n"
"    mediump vec3 MaterialAmbientColor = vec3(0.2, 0.2, 0.2) * MaterialDiffuseColor;\n"
"    mediump vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);\n"
"\n"
"    //distance to light\n"
"  mediump   float distance  = length(LightPosition_world - position_worldspace);\n"
"    mediump float distance2 = distance * distance;\n"
"\n"
"    mediump vec3 n = normalize(Normal_camera);\n"
"    // direction from fragment to light\n"
"    mediump vec3 l = normalize(LightDirection_camera);\n"
"\n"
"    // cosine angle between normal and the light direction\n"
"    mediump float cosTheta = clamp(dot(n, l), 0.0,1.0);\n"
"\n"
"    // mediump vector towards camera\n"
"    mediump vec3 E  = normalize(EyeDirection_camera);\n"
"    // direction of reflection\n"
"    mediump vec3 R  = reflect(-l, n);\n"
"    // cosine angle between eye mediump vector and reflection mediump vector\n"
"    mediump float cosAlpha = clamp( dot(E, R), 0.0, 1.0);\n"
"\n"
"    mediump vec4 color = vec4(MaterialAmbientColor + \n"
"            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance2) +\n"
"            MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5.0) / (distance2),\n"
"            ALPHA);\n"
"\n"
"    mediump vec3 pose = vec3(0.1 * (position_worldspace.x + 5.0), position_worldspace.y, 0.1 * (position_worldspace.z + 5.0));\n"
"    mediump vec3 noise_pos = pose * 15.0;\n"
"    mediump float noise_base =  7.0 * (position_worldspace.x + position_worldspace.z +  0.2 * position_worldspace.y);\n"
"    mediump float noise_val = sin(noise_base + 4.2 * (turbulence(position_worldspace)));\n"
"    noise_val = 1.0 - noise_val;\n"
"\n"
"    color = noise_val * color;\n"
"    color.a = ALPHA;\n"
"    gl_FragColor = color; \n"
"}";
#endif
