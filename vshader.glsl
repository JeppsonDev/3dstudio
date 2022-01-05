#version 330

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec3 u_LightPosition;

uniform mat4 u_LightSpaceMatrix; //For shadow mapping

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec4 color; // Color to fragment
out vec2 v_TexCoords; //Tex coords to framgent

out vec4 FragPosLightSpace; //shadow mapping

out vec3 fN; // Normal vector
out vec3 fE; // Direction of the viewer
out vec3 fL; // Direction of the light

void main()
{
    v_TexCoords = vTexCoords;

    //Do this to make sure the normal follow model matrix
    fN = (u_Model * vec4(vNormal.xyz, 0.0)).xyz; //surface normal
    fE = vec3(u_Model * vec4(vPosition, 1.0)); //vertex position
    fL = normalize(u_LightPosition - fE); //Calculate direction FROM surface TO light source

    vec4 FragPosLightSpace = u_LightSpaceMatrix * vec4(fE, 1.0); //For shadow mapping

    gl_Position = u_Projection*u_View*u_Model*vec4(fE, 1.0);
}
