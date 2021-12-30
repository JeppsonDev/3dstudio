#version 330

uniform sampler2D u_Texture;

in vec4 color;
in vec2 v_TexCoords;

out vec4 fcolor;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoords);
    
    if(length(v_TexCoords) > 0)
    {
        fcolor = texColor * color;
    }
    else
    {
        fcolor = color;
    }
}