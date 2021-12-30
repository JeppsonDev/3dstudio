#version 330

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_LightPosition;
uniform vec3 u_AmbientLight;
uniform vec3 u_LightIntensity;
uniform vec3 u_AmbientConstant;
uniform vec3 u_DiffuseConstant;
uniform vec3 u_SpecularConstant;
uniform float u_Shininess;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec4 color; // Color to fragment
out vec2 v_TexCoords; //Tex coords to framgent

out vec3 fN; // Normal vector
out vec3 fE; // Direction of the viewer
out vec3 fL; // Direction of the light

void main()
{
    v_TexCoords = vTexCoords;

    fN = vNormal; //surface normal
    fE = vec3(u_Model * vec4(vPosition, 1.0)); //vertex position
    fL = normalize(u_LightPosition - fE); //Calculate direction FROM surface TO light source

    vec3 Ia = u_AmbientLight; //ambient light
    vec3 Id = vec3(1.0, 1.0, 1.0); //diffuse light
    vec3 Is = vec3(1.0, 1.0, 1.0) * 0.25; //specular light

    vec3 ka = u_AmbientConstant; //ambient constant
    vec3 kd = u_DiffuseConstant; //diffuse constant
    vec3 ks = u_SpecularConstant; //specular constant


    vec3 l = fL; //direction to light source from surface
    vec4 v = normalize(vec4(0.0, 0.0, -4.0, 0.0)); //direction to the viewer
    float a = u_Shininess;

    vec3 r = normalize(reflect(l, fN));//direction of reflection     //2 * (dot(fN, l)) * fN - l;

    vec3 Iambient = Ia * ka; //Multiply the ambient light by the ambient constant
    vec3 Idiffuse = Id * kd * max(dot(fN, l), 0.0); //take the angle between the surface normal and the light direction and multiply by the light colour and diffuse constant
    vec3 Ispecular = Is * ks * pow(max(dot(v.xyz, r), 0.0), a);

    color.rgb = (Iambient + Idiffuse + Ispecular) * u_LightIntensity;
    color.a = 1.0;

    gl_Position = u_Projection*u_View*u_Model*vec4(vPosition, 1.0);
}
