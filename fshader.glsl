#version 330

uniform sampler2D u_Texture;
uniform sampler2D u_DepthTexture;

uniform bool u_ShouldRenderTexture;

uniform vec3 u_CameraPosition;

uniform vec3 u_LightPosition;
uniform vec3 u_AmbientLight;
uniform vec3 u_LightIntensity;
uniform vec3 u_AmbientConstant;
uniform vec3 u_DiffuseConstant;
uniform vec3 u_SpecularConstant;
uniform float u_Shininess;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} fs_in;

out vec4 fcolor;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDirection)
{
    vec3 projectedCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projectedCoords = projectedCoords * 0.5 + 0.5;
    float closestDepth = texture(u_DepthTexture, projectedCoords.xy).r; 
    float currentDepth = projectedCoords.z;

    float bias = max(0.05 * (1.0 - dot(fs_in.normal, lightDirection)), 0.005);

    //Percentage Closer Filtering
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(u_DepthTexture, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float percentageCloserFiltering = texture(u_DepthTexture, projectedCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > percentageCloserFiltering ? 1.0 : 0.0;        
        }    
    }

    shadow /= 9.0;

    return shadow;
}

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
    float shadow = ShadowCalculation(fs_in.fragPosLightSpace, lightDirection);

    vec3 Idiffuse = u_LightIntensity * u_DiffuseConstant * max(dot(normal, lightDirection), 0.0);

    if(dot(normal, lightDirection) > 0.0)
    {
        vec3 Ispecular = u_LightIntensity * u_SpecularConstant * pow(max(dot(viewDirection, reflectionDirection), 0.0), u_Shininess);

        color = vec4(Iambient + (1.0 - shadow) * (Idiffuse + Ispecular), 1.0);
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