#version 330

uniform sampler2D u_Texture;
uniform bool u_ShouldRenderTexture;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
    vec4 color;
} fs_in;

out vec4 fcolor;

void main()
{
    vec4 texColor = texture(u_Texture, fs_in.texCoords);

    if(u_ShouldRenderTexture)
    {
        fcolor = texColor * fs_in.color;
    }
    else
    {
        fcolor = fs_in.color;
    }
}