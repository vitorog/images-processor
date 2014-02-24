#version 400
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D texture;

void main(void)
{
    ivec2 texture_size = textureSize2D(texture,0);
    if(gl_FragCoord.x > 0 &&
            gl_FragCoord.x < texture_size.x &&
            gl_FragCoord.y > 0 &&
            gl_FragCoord.y < texture_size.y){
        mat3x3 gx = mat3x3(
                    -1.0f,-2.0f,-1.0f, //first column
                    0.0f,0.0f,0.0f, //second column
                    1.0f, 2.0f, 1.0f); //third column

        mat3x3 gy = mat3x3(
                    1.0f,0.0f,-1.0f, //first column
                    2.0f,0.0f,-2.0f, //second column
                    1.0f,0.0f,-1.0f); //third column

        vec2 steps = vec2(1.0f/texture_size.x, 1.0f/texture_size.y);

        float sum_color_x;
        float sum_color_y;
        for(int x=0; x<3; x++){
            for(int y=0; y<3; y++){
                vec2 coords = tex_coords;
                coords.x += (x-1)*steps.x;
                coords.y += (y-1)*steps.y;
                vec4 color = texture2D(texture, coords);
                float gs_color = (color.x + color.y + color.z)/3.0f;

                sum_color_x+=gs_color*gx[y][x];
                sum_color_y+=gs_color*gy[y][x];
            }
        }
        float mag = sqrt(pow(sum_color_x,2.0f) + pow(sum_color_y,2.0f));
        frag_color.xyz = vec3(mag);
        frag_color.w = 1.0f;

    }else{
        frag_color = vec4(gl_FragCoord.x/texture_size.x,0.0f,0.0f,1.0f);
    }
}
