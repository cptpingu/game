#version 120

uniform sampler2D tex;

varying float vCubeColor;
varying float vFaceColor;

void main()
{
  vec4 color = texture2D(tex, gl_TexCoord[0].st);
  gl_FragColor = color;

  gl_FragColor.x += vCubeColor + vFaceColor;
  gl_FragColor.y += vCubeColor + vFaceColor;
  gl_FragColor.z += vCubeColor + vFaceColor * 1000;
}
