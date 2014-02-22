#version 400
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D texture;

void main(void)
{
  ivec2 texture_size = textureSize2D(texture,0);
  int blur_size = 10;
  int min_x = int(gl_FragCoord.x) - int(blur_size/2.0f);
  int max_x = int(gl_FragCoord.x) + int(blur_size/2.0f);
  int min_y = int(gl_FragCoord.y) - int(blur_size/2.0f);
  int max_y = int(gl_FragCoord.y) + int(blur_size/2.0f);

  if(min_x < 0){ min_x = 0;  }
  if(max_x >= texture_size.x) { max_x = texture_size.x - 1; }
  if(min_y < 0){ min_y = 0;  }
  if(max_y >= texture_size.y) { max_y = texture_size.y - 1; }

  vec4 color = vec4(0.0f,0.0f,0.0f,1.0f);
  for(int x = min_x; x <= max_x; x++){
      for(int y = min_y; y <= max_y; y++){
        vec2 position = ( vec2(x,y) / texture_size.xy );
        color += texture2D(texture, position);
      }
  }
  color /= (blur_size*blur_size);
  frag_color = color;
}
