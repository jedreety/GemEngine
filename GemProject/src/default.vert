#version 330
// specify we are indeed using modern opengl

layout(location = 0) in vec3 vertex_position; // vertex position attribute
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

// Uniform block for matrices
layout(std140) uniform Matrices {
    mat4 projectionMatrix;
    mat4 viewMatrix;
};

uniform mat4 modelMatrix;

out vec3 Normals;

void main(void) {
	Normals = aNormal;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.0); // set vertex position
}