#version 330

uniform sampler2D u_Texture;
uniform sampler2D u_ShadowMap; //For shadow mapping
uniform bool u_ShouldRenderTexture;

//Light settings
uniform vec3 u_AmbientLight;
uniform vec3 u_LightIntensity;
uniform vec3 u_AmbientConstant;
uniform vec3 u_DiffuseConstant;
uniform vec3 u_SpecularConstant;
uniform float u_Shininess;

in vec4 color;
in vec2 v_TexCoords;

in vec4 FragPosLightSpace; //shadow mapping
in vec3 fN; // Normal vector
in vec3 fE; // Direction of the viewer
in vec3 fL; // Direction of the light

out vec4 fcolor;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(u_ShadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    vec3 Ia = u_AmbientLight; //ambient light
    vec3 Id = vec3(1.0, 1.0, 1.0); //diffuse light
    vec3 Is = vec3(1.0, 1.0, 1.0) * 0.25; //specular light

    vec3 ka = u_AmbientConstant; //ambient constant
    vec3 kd = u_DiffuseConstant; //diffuse constant
    vec3 ks = u_SpecularConstant; //specular constant

    vec3 l = fL; //direction to light source from surface
    vec4 v = vec4(-normalize(fE), 0.0); //direction to the viewer
    float a = u_Shininess;

    vec3 r = normalize(reflect(l, fN));//direction of reflection     //2 * (dot(fN, l)) * fN - l;

    vec3 Iambient = Ia * ka; //Multiply the ambient light by the ambient constant
    vec3 Idiffuse = Id * kd * max(dot(fN, l), 0.0); //take the angle between the surface normal and the light direction and multiply by the light colour and diffuse constant
    vec3 Ispecular = Is * ks * pow(max(dot(v.xyz, r), 0.0), a);

    float shadow = ShadowCalculation(FragPosLightSpace);
    float s = 1.0 - shadow;

    vec4 light = vec4(0.0f, shadow, 0.0f, 1.0f);
    light.rgb = ((Iambient + (s * (Idiffuse + Ispecular))) * u_LightIntensity * 2.5);
    vec4 texColor = texture(u_Texture, v_TexCoords);

    if(u_ShouldRenderTexture)
    {
        fcolor = texColor * light;
    }
    else
    {
        fcolor = light;
    }
}