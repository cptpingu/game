#version 120

attribute float selected;

varying float select;

void main()
{
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ftransform();

  select = selected;
}
