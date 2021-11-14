#version 330

uniform mat4 u_Translate;

in vec2 vPosition;

void
main()
{
    gl_Position =  u_Translate * vec4(vPosition, 0.0, 20.0);
}
