#version 330 core

in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D texture1;


void main() {
    //FragColor = vec4(ourColor, 1.0f);
	FragColor = texture(texture1, TexCoord);
}  
