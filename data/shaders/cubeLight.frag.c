#version 120

uniform sampler2D tex;

uniform float cube_color;
varying float vFaceColor;

uniform float vdistance;
//varying float Distance;

void main()
{
  vec4 color = texture2D(tex, gl_TexCoord[0].st);
  gl_FragColor = color;

  gl_FragColor.x =  color.x + cube_color  +vdistance;
  gl_FragColor.y =  color.y + cube_color ;
  gl_FragColor.z =  color.z + cube_color + vFaceColor;
}
