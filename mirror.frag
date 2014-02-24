#version 400
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D texture;

void main(void)
{
  ivec2 texture_size = textureSize2D(texture,0);
  if(gl_FragCoord.x <= texture_size.x/2.0f){
    vec4 tex_color = texture2D(texture, tex_coords);
    frag_color = tex_color;
  }else{
    vec2 mirror_cords = vec2(0.5f - (tex_coords.x - 0.5f),tex_coords.y);
    vec4 tex_color = texture2D(texture, mirror_cords);
    frag_color = tex_color;
  }
}
