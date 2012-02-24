uniform sampler2D tex;

void main()
{
  vec4 color = texture2D(tex, gl_TexCoord[0].st);
  color.x = 1.0 - color.x;
  color.y = 1.0 - color.y;
  color.z = 1.0 - color.z;
  gl_FragColor = color;
}
