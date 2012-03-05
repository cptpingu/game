#version 120

varying vec4 pos;
varying vec4 rawPos;
varying vec3 normal;

void main()
{
    normal = gl_NormalMatrix * gl_Normal;
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();
    pos = gl_ModelViewMatrix * gl_Vertex;
    rawPos = gl_Vertex;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_TexCoord[1] = gl_MultiTexCoord1;
    gl_TexCoord[2] = gl_MultiTexCoord2;
}
