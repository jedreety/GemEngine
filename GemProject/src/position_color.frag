#version 330 core

// Input from vertex shader
in vec3 vertexColor;

// Output color
out vec4 FragColor;

void main() {
    // Use the vertex color directly as the fragment color
    FragColor = vec4(vertexColor, 1.0);
}