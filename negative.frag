#version 400
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D texture;

void main(void)
{
  vec4 tex_color = texture2D(texture, tex_coords);
  frag_color = 1 - tex_color;
}
