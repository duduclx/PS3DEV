attribute vec3 position;
attribute vec3 color;

uniform mat4 ProjMatrix;
uniform mat4 TransMatrix;

void
main(void)
{
  gl_Position = ProjMatrix * (TransMatrix * vec4(position,1));
}
