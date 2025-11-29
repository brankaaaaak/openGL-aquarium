#version 330 core
layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inUV;

uniform mat3 uTransform;

out vec2 texCoord;

void main()
{
    vec3 pos = uTransform * vec3(inPos, 1.0);
    gl_Position = vec4(pos.xy, 0.0, 1.0);
    texCoord = inUV;
}
