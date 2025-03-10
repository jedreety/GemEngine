#include <Gem/Graphics/shapes/cube.h>
#include <iostream>

namespace Gem {
    namespace Graphics {
        namespace Shapes {

            Cube::Cube(float size)
                : size_(size),
                VAO_(),
                VBO_(GL_ARRAY_BUFFER),
                EBO_(GL_ELEMENT_ARRAY_BUFFER) {

                generateData();
                initialize();
            }

            Cube::~Cube() {
                // Cleanup is handled by the destructors of VAO_, VBO_, and EBO_
            }

            void Cube::generateData() {
                // Define the 8 vertices of the cube
                // Each vertex has position (xyz) and normal (xyz) components
                // Front face: bottom-left, bottom-right, top-right, top-left
                // Back face: bottom-left, bottom-right, top-right, top-left

                float halfSize = size_ / 2.0f;

                // Vertex data: positions and normals
                vertices_ = {
                    // Front face (z = +halfSize)
                    // Position            // Normal
                    -halfSize, -halfSize,  halfSize,   0.0f, 0.0f, 1.0f, // 0: front bottom-left
                     halfSize, -halfSize,  halfSize,   0.0f, 0.0f, 1.0f, // 1: front bottom-right
                     halfSize,  halfSize,  halfSize,   0.0f, 0.0f, 1.0f, // 2: front top-right
                    -halfSize,  halfSize,  halfSize,   0.0f, 0.0f, 1.0f, // 3: front top-left

                    // Back face (z = -halfSize)
                    -halfSize, -halfSize, -halfSize,   0.0f, 0.0f, -1.0f, // 4: back bottom-left
                     halfSize, -halfSize, -halfSize,   0.0f, 0.0f, -1.0f, // 5: back bottom-right
                     halfSize,  halfSize, -halfSize,   0.0f, 0.0f, -1.0f, // 6: back top-right
                    -halfSize,  halfSize, -halfSize,   0.0f, 0.0f, -1.0f, // 7: back top-left

                    // Right face (x = +halfSize)
                     halfSize, -halfSize,  halfSize,   1.0f, 0.0f, 0.0f, // 8: right bottom-front
                     halfSize, -halfSize, -halfSize,   1.0f, 0.0f, 0.0f, // 9: right bottom-back
                     halfSize,  halfSize, -halfSize,   1.0f, 0.0f, 0.0f, // 10: right top-back
                     halfSize,  halfSize,  halfSize,   1.0f, 0.0f, 0.0f, // 11: right top-front

                    // Left face (x = -halfSize)
                    -halfSize, -halfSize, -halfSize,  -1.0f, 0.0f, 0.0f, // 12: left bottom-back
                    -halfSize, -halfSize,  halfSize,  -1.0f, 0.0f, 0.0f, // 13: left bottom-front
                    -halfSize,  halfSize,  halfSize,  -1.0f, 0.0f, 0.0f, // 14: left top-front
                    -halfSize,  halfSize, -halfSize,  -1.0f, 0.0f, 0.0f, // 15: left top-back

                    // Top face (y = +halfSize)
                    -halfSize,  halfSize,  halfSize,   0.0f, 1.0f, 0.0f, // 16: top left-front
                     halfSize,  halfSize,  halfSize,   0.0f, 1.0f, 0.0f, // 17: top right-front
                     halfSize,  halfSize, -halfSize,   0.0f, 1.0f, 0.0f, // 18: top right-back
                    -halfSize,  halfSize, -halfSize,   0.0f, 1.0f, 0.0f, // 19: top left-back

                    // Bottom face (y = -halfSize)
                    -halfSize, -halfSize, -halfSize,   0.0f, -1.0f, 0.0f, // 20: bottom left-back
                     halfSize, -halfSize, -halfSize,   0.0f, -1.0f, 0.0f, // 21: bottom right-back
                     halfSize, -halfSize,  halfSize,   0.0f, -1.0f, 0.0f, // 22: bottom right-front
                    -halfSize, -halfSize,  halfSize,   0.0f, -1.0f, 0.0f  // 23: bottom left-front
                };

                // Index data: 6 faces, 2 triangles per face, 3 indices per triangle
                indices_ = {
                    // Front face
                    0, 1, 2,
                    2, 3, 0,

                    // Back face
                    4, 7, 6,
                    6, 5, 4,

                    // Right face
                    8, 9, 10,
                    10, 11, 8,

                    // Left face
                    12, 15, 14,
                    14, 13, 12,

                    // Top face
                    16, 17, 18,
                    18, 19, 16,

                    // Bottom face
                    20, 23, 22,
                    22, 21, 20
                };
            }

            const std::vector<GLfloat>& Cube::getVertices() const {
                return vertices_;
            }

            const std::vector<GLuint>& Cube::getIndices() const {
                return indices_;
            }

            void Cube::initialize() {
                // Generate and bind VAO, VBO, and EBO
                VAO_.generate();
                VBO_.generate();
                EBO_.generate();

                VAO_.bind();

                // Upload vertex and index data to GPU
                VBO_.set_data(vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
                EBO_.set_data(indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

                // Link the position attribute (location = 0)
                VAO_.link_attrib(
                    VBO_,                   // VBO
                    0,                      // Attribute location in the shader
                    3,                      // Number of components (x, y, z)
                    GL_FLOAT,               // Data type
                    6 * sizeof(GLfloat),    // Stride (total size of a vertex)
                    (void*)0,               // Offset (start of position data)
                    GL_FALSE                // Normalized
                );

                // Link the normal attribute (location = 2)
                VAO_.link_attrib(
                    VBO_,                             // VBO
                    2,                                // Attribute location in the shader
                    3,                                // Number of components (nx, ny, nz)
                    GL_FLOAT,                         // Data type
                    6 * sizeof(GLfloat),              // Stride (total size of a vertex)
                    (void*)(3 * sizeof(GLfloat)),     // Offset (after position data)
                    GL_FALSE                          // Normalized
                );

                // Unbind VAO to prevent accidental modifications
                VAO_.unbind();
            }

            void Cube::render() const {
                VAO_.bind();
                Gem::GL::draw_elements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, 0);
                VAO_.unbind();
            }

        } // namespace Shapes
    } // namespace Graphics
} // namespace Gem