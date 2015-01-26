#version 400
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D texture;

void main(void)
{
  ivec2 texture_size = textureSize2D(texture,0);
  vec4 tex_color = texture2D(texture, tex_coords);
  
  //Some blur
  tex_color += texture2D(texture, tex_coords.xy + 0.001f);
  tex_color += texture2D(texture, tex_coords.xy + 0.002f);
  tex_color += texture2D(texture, tex_coords.xy + 0.003f);  
  tex_color = tex_color / 4.0f;
  
  float x_dist = gl_FragCoord.x - texture_size.x/2.0f;
  float y_dist = gl_FragCoord.y - texture_size.y/2.0f;  
  float radius = 250.0f;
  //Check if point is inside the circle with the given radius
  if((x_dist*x_dist) + (y_dist*y_dist) > radius*radius){
	frag_color = vec4(0.1f,0.1f,0.1f,1.0f) * tex_color;
  }else{
	float lum = (tex_color.r + tex_color.g + tex_color.b)/3.0f;  
	if(lum <= 0.9f){
		frag_color = vec4(0.0f,1.0f,0.0f,1.0f)*lum*1.5f;
	}else{
		frag_color = tex_color;
	}
  }
}