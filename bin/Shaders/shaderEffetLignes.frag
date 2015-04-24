#version 430 core

layout (location = 0) out vec4 color;
uniform sampler2D screenTexture;

in vec2 texcoords;

const float offset = 1.0 / 300;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );

    float kernel[9] = float[](
		1.0, 1.0, 1.0,
		1.0, -8.0, 1.0,
		1.0, 1.0, 1.0
	);
    
    vec3 col;
    for(int i = 0; i < 9; i++) {
		vec3 sampling = vec3(texture(screenTexture, texcoords.st + offsets[i]));
        col += sampling * kernel[i];
	}
    
    color = vec4(col, 1.0);
}  