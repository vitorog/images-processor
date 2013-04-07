#version 400
in vec3 vertex_position;
in vec3 vertex_texture_coords;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec2 tex_coords;

void main(void)
{
  tex_coords = vertex_texture_coords;
  gl_Position = (projection_matrix * view_matrix * model_matrix) * vec4(vertex_position, 1.0f);
}
