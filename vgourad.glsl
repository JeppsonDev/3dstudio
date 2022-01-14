#version 330

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec3 u_CameraPosition;
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

out VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
    vec4 color;
} vs_out;

void main()
{
    vs_out.fragPos = vec3(u_Model * vec4(vPosition, 1.0));
    vs_out.normal = normalize(transpose(inverse(mat3(u_Model))) * normalize(vNormal));
    vs_out.texCoords = vTexCoords;
    
    vec3 viewDirection = normalize(vec3(u_CameraPosition - vs_out.fragPos)); //direction to the viewer
    vec3 lightDirection = normalize(u_LightPosition - vs_out.fragPos); //direction of light

    vec3 normal = vs_out.normal;

    vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));//direction of reflection     //2 * (dot(fN, l)) * fN - l;

    vec3 Iambient = u_AmbientLight * u_AmbientConstant; //Multiply the ambient light by the ambient constant
    vec3 Idiffuse = u_LightIntensity * u_DiffuseConstant * max(dot(normal, lightDirection), 0.0); //take the angle between the surface normal and the light direction and multiply by the light colour and diffuse constant

    if(dot(normal, lightDirection) > 0.0)
    {
        vec3 Ispecular = u_LightIntensity * u_SpecularConstant * pow(max(dot(viewDirection, reflectionDirection), 0.0), u_Shininess);
        vs_out.color = vec4(Iambient + Idiffuse + Ispecular, 1.0);
    }
    else
    {
        vs_out.color = vec4(Iambient + Idiffuse, 1.0);  
    }

    gl_Position = u_Projection*u_View*u_Model*vec4(vPosition, 1.0);
}