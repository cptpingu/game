uniform sampler2D tex;

void main()
{
  vec4 color = texture2D(tex, gl_TexCoord[0].st);
  color.x = 255.0f - color.x;
  color.y = 255.0f - color.y;
  color.z = 255.0f - color.z;
  gl_FragColor = color;
}
