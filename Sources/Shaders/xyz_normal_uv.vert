#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUV;

uniform mat4 MV;
uniform mat3 N;
uniform mat4 MVP;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main()
{
    Position = (MV * vec4(vPos, 1.0)).xyz;
    Normal = normalize(N * vNormal);
    UV = vUV;

    gl_Position = MVP * vec4(vPos, 1.0);
}