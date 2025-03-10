#include <Gem/Graphics/shapes/plane.h>
#include <iostream>

namespace Gem {
    namespace Graphics {
        namespace Shapes {

            Plane::Plane(float width, float height, unsigned int segments)
                : width_(width), height_(height), segments_(segments),
                VAO_(),
                VBO_(GL_ARRAY_BUFFER),
                EBO_(GL_ELEMENT_ARRAY_BUFFER) {

                generateData();
                initialize();
            }

            Plane::~Plane() {
                // Cleanup is handled by the destructors of VAO_, VBO_, and EBO_
            }

            void Plane::generateData() {
                // Calculate the number of vertices and indices
                unsigned int numVerticesX = segments_ + 1;
                unsigned int numVerticesZ = segments_ + 1;
                unsigned int numVertices = numVerticesX * numVerticesZ;
                unsigned int numIndices = segments_ * segments_ * 6; // 2 triangles per segment square, 3 indices per triangle

                // Resize vectors to avoid dynamic resizing
                vertices_.resize(numVertices * 6); // x, y, z, nx, ny, nz for each vertex
                indices_.resize(numIndices);

                // Generate vertices
                float halfWidth = width_ / 2.0f;
                float halfHeight = height_ / 2.0f;
                float segmentWidth = width_ / static_cast<float>(segments_);
                float segmentHeight = height_ / static_cast<float>(segments_);

                unsigned int vertexIndex = 0;
                for (unsigned int z = 0; z < numVerticesZ; ++z) {
                    for (unsigned int x = 0; x < numVerticesX; ++x) {
                        // Position
                        float posX = -halfWidth + x * segmentWidth;
                        float posY = 0.0f; // Y is up in this coordinate system
                        float posZ = -halfHeight + z * segmentHeight;

                        // Normal (pointing up)
                        float nx = 0.0f;
                        float ny = 1.0f;
                        float nz = 0.0f;

                        // Add vertex data
                        vertices_[vertexIndex++] = posX;
                        vertices_[vertexIndex++] = posY;
                        vertices_[vertexIndex++] = posZ;
                        vertices_[vertexIndex++] = nx;
                        vertices_[vertexIndex++] = ny;
                        vertices_[vertexIndex++] = nz;
                    }
                }

                // Generate indices
                unsigned int indexCount = 0;
                for (unsigned int z = 0; z < segments_; ++z) {
                    for (unsigned int x = 0; x < segments_; ++x) {
                        unsigned int topLeft = z * numVerticesX + x;
                        unsigned int topRight = topLeft + 1;
                        unsigned int bottomLeft = (z + 1) * numVerticesX + x;
                        unsigned int bottomRight = bottomLeft + 1;

                        // First triangle (top-left, bottom-left, bottom-right)
                        indices_[indexCount++] = topLeft;
                        indices_[indexCount++] = bottomLeft;
                        indices_[indexCount++] = bottomRight;

                        // Second triangle (top-left, bottom-right, top-right)
                        indices_[indexCount++] = topLeft;
                        indices_[indexCount++] = bottomRight;
                        indices_[indexCount++] = topRight;
                    }
                }
            }

            const std::vector<GLfloat>& Plane::getVertices() const {
                return vertices_;
            }

            const std::vector<GLuint>& Plane::getIndices() const {
                return indices_;
            }

            void Plane::initialize() {
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

            void Plane::render() const {
                VAO_.bind();
                Gem::GL::draw_elements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, 0);
                VAO_.unbind();
            }

        } // namespace Shapes
    } // namespace Graphics
} // namespace Gem