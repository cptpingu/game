varying vec3 N;
varying vec3 v;
uniform sampler2D tex;

attribute float Temps;
varying  float vTemps;


void main(void)
{
    //vec 4 lighPosWorld = vec4(0.0,0.0,7.0,1.0);



   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);
   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;


   //lightDir = normalize((gl_ModelViewMatrix*lighPosWorld - v).xyz);

   vTemps = Temps;
   //vDistance = Distance;
}
