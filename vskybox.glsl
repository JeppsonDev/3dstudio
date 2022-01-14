#version 330 core
layout (location = 0) in vec3 vPosition;

out VS_OUT {
    vec3 texCoords;
} vs_out;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
    vs_out.texCoords = vPosition;
    vec4 pos = u_Projection * u_View * vec4(vPosition, 1.0);
    gl_Position = pos.xyww;
}  