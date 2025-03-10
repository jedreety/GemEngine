#version 330 core

layout(location = 0) in vec3 vertex_position; // vertex position attribute
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

// Uniform block for matrices
layout(std140) uniform Matrices {
    mat4 projectionMatrix;
    mat4 viewMatrix;
};

uniform mat4 modelMatrix;

// Output to fragment shader
out vec3 vertexColor;

void main() {
    // Pass the position as color (normalized to 0-1 range)
    vertexColor = vertex_position * 0.5 + 0.5; // Transform from [-1,1] to [0,1] range
    
    // Set vertex position
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.0);
}