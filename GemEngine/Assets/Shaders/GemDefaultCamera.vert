#version 330 core

layout(location = 0) in vec3 vertex_position; // vertex position attribute

// Uniform block for matrices
layout(std140) uniform Matrices {
    mat4 projectionMatrix;
    mat4 viewMatrix;
};

void main() {
    gl_Position = projectionMatrix * viewMatrix * vec4(vertex_position, 1.0); // set vertex position
}
