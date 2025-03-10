#version 330 core

// Inputs from the vertex shader
in vec3 Normals;    // Fragment normal

// Output color of the fragment
out vec4 FragColor;

// Uniform sampler for the 2D texture
uniform sampler2D texture_diffuse;

void main()
{
    // Since the object is a circle, we assume the normals are in the XY plane
    // and are already normalized (i.e., length is 1)
    
    // Map normals from [-1, 1] to [0, 1] to use as texture coordinates
    vec2 texCoord = Normals.xy * 0.5 + 0.5;

    // Set the fragment color to the sampled texture color
    FragColor = texture(texture_diffuse, texCoord);
}
