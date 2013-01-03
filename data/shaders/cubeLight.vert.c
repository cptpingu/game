#version 120

attribute float face_color;
varying float vFaceColor;


//attribute float Distance;
//varying float vdistance;




void main()
{
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ftransform();
  vFaceColor = face_color;

  //vdistance = Distance;
}
