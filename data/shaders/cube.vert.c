#version 120

uniform float cube_color;
attribute float face_color;

varying float vCubeColor;
varying float vFaceColor;

void main()
{
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ftransform();

  vCubeColor = cube_color;
  vFaceColor = face_color;
}
