#version 120

varying vec4 pos;
varying vec4 rawPos;
varying vec3 normal;

const float SIZE = 100.0;

void main()
{
  float heightColor = (rawPos.z + SIZE) / (2 * SIZE);
  gl_FragColor.x = heightColor;
  gl_FragColor.y = heightColor;
  gl_FragColor.z = heightColor;
  gl_FragColor.w = 1.0;
}
