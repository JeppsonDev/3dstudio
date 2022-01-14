#version 330

uniform sampler2D u_Texture;

uniform bool u_ShouldRenderTexture;
uniform float u_OutlineThickness;

uniform vec3 u_CameraPosition;

uniform vec3 u_LightPosition;
uniform vec3 u_AmbientLight;
uniform vec3 u_LightIntensity;
uniform vec3 u_AmbientConstant;
uniform vec3 u_DiffuseConstant;
uniform vec3 u_SpecularConstant;
uniform float u_Shininess;

const float levels = 2.0;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
} fs_in;

out vec4 fcolor;

void main()
{
    vec4 texColor;
    texColor = texture(u_Texture, fs_in.texCoords);

    vec3 viewDirection = normalize(vec3(u_CameraPosition - fs_in.fragPos)); //direction to the viewer
    vec3 lightDirection = normalize(u_LightPosition - fs_in.fragPos); //direction of light

    vec3 normal = fs_in.normal;

    vec3 reflectionDirection = normalize(reflect(-lightDirection, normal));//direction of reflection     //2 * (dot(fN, l)) * fN - l;

    vec3 Iambient =  u_AmbientLight * u_AmbientConstant; //Multiply the ambient light by the ambient constant

    vec4 color;

    float intensity = max(dot(normal, lightDirection), 0.0);
    float level = floor(intensity * levels);
    intensity = level / levels;

    vec3 Idiffuse = u_LightIntensity * u_DiffuseConstant * intensity;

    if(dot(normal, lightDirection) > 0.0)
    {
        float intensitySpecular = pow(max(dot(viewDirection, reflectionDirection), 0.0), u_Shininess);
        float levelSpecular = floor(intensitySpecular * levels);
        intensitySpecular = levelSpecular / levels;

        vec3 Ispecular = u_LightIntensity * u_SpecularConstant * intensitySpecular;

        color = vec4(Iambient + Idiffuse + Ispecular, 1.0);
    }
    else
    {
        color = vec4(Iambient + Idiffuse, 1.0);
    }

    if(u_ShouldRenderTexture)
    {
        fcolor = texColor * color;
    }
    else
    {
        fcolor = color;
    }
}