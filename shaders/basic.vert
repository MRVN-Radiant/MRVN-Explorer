/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUV;

uniform mat4 transform;

out vec3 normal;
out vec2 uv;

void main()
{
    gl_Position = transform * vec4( vPos, 1.0f );
    normal = vNormal;
    uv = vUV;
}
