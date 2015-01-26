#version 400
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D texture;

void main(void)
{
  vec4 tex_color = texture2D(texture, tex_coords);
  float color = (tex_color.x + tex_color.y + tex_color.z)/3.0f; 
  frag_color = vec4(color,color,color,1.0f);
}
