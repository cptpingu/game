#version 120

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

varying vec4 pos;
varying vec4 rawPos;
varying vec3 normal;

float[3] computeTextureCoeff(float height)
{
  float z = height * 255;
  float[3] coeffs;
  if (z < 60)
  {
    coeffs[0] = 1.0;
    coeffs[1] = 0.0;
    coeffs[2] = 0.0;
  }
  else if (z < 130)
  {
    coeffs[0] = 1.0 - (z - 60.0) / 70.0;
    coeffs[1] = (z - 60.0) / 70.0;
    coeffs[2] = 0.0;
  }
  else if (z < 180)
  {
    coeffs[0] = 0.0;
    coeffs[1] = 1.0;
    coeffs[2] = 0.0;
  }
  else if (z < 220)
  {
    coeffs[0] = 0.0;
    coeffs[1] = 1.0 - (z - 180.0) / 40.0;
    coeffs[2] = (z - 180.0) / 40.0;
  }
  else
  {
    coeffs[0] = 0.0;
    coeffs[1] = 0.0;
    coeffs[2] = 1.0;
  }

  return coeffs;
}

void main()
{
  float[3] coeffs = computeTextureCoeff(rawPos.z / 100.0);
  vec4 color0 = texture2D(tex0, gl_TexCoord[0].st);
  vec4 color1 = texture2D(tex1, gl_TexCoord[1].st);
  vec4 color2 = texture2D(tex2, gl_TexCoord[2].st);

  gl_FragColor.x = color0.x * coeffs[0] + color1.x * coeffs[1] + color2.x * coeffs[2];
  gl_FragColor.y = color0.y * coeffs[0] + color1.y * coeffs[1] + color2.y * coeffs[2];
  gl_FragColor.z = color0.z * coeffs[0] + color1.z * coeffs[1] + color2.z * coeffs[2];

  gl_FragColor.w = 1.0;
}
