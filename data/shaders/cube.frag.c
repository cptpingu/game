#version 120

uniform sampler2D tex;

varying int select;

void main()
{
  vec4 color = texture2D(tex, gl_TexCoord[0].st);
  gl_FragColor = color;

  gl_FragColor.x += select * 1.0;
  gl_FragColor.y += select * 1.0;
  gl_FragColor.z += select * 1.0;
}
