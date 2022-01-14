#version 330

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_LightSpaceMatrix;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} vs_out;

void main()
{
    vs_out.fragPos = vec3(u_Model * vec4(vPosition, 1.0));
    vs_out.normal = normalize(transpose(inverse(mat3(u_Model))) * normalize(vNormal));
    vs_out.texCoords = vTexCoords;
    vs_out.fragPosLightSpace = u_LightSpaceMatrix * u_Model * vec4(vPosition, 1.0);

    gl_Position = u_Projection*u_View*u_Model*vec4(vPosition, 1.0);
}