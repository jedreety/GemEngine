#include <Gem/Graphics/shapes/sphere.h>
#include <iostream>
#include <cmath>

namespace Gem {
    namespace Graphics {
        namespace Shapes {

            constexpr float M_PI = 3.14159265358979;
            
            Sphere::Sphere(float radius, unsigned int latitudeSegments, unsigned int longitudeSegments)
				: radius_(radius), latitudeSegments_(latitudeSegments), longitudeSegments_(longitudeSegments),
				VAO_(),
				VBO_(GL_ARRAY_BUFFER),
				EBO_(GL_ELEMENT_ARRAY_BUFFER) {

                generateData();
                initialize();
            }

            Sphere::~Sphere() {
				// Already done in destructor
            }

			void Sphere::generateData() {
				const float twoPi = 2.0f * M_PI;
				const float pi = M_PI;

				const unsigned int numVertices = (latitudeSegments_ + 1) * (longitudeSegments_ + 1);
				const unsigned int numIndices = latitudeSegments_ * (longitudeSegments_ + 1) * 2;

				// Resize vectors to avoid dynamic resizing
				vertices_.resize(numVertices * 6); // x, y, z, nx, ny, nz for each vertex
				indices_.resize(numIndices);

				// Precompute sine and cosine values for longitude and latitude
				std::vector<float> sinX(longitudeSegments_ + 1);
				std::vector<float> cosX(longitudeSegments_ + 1);
				std::vector<float> sinY(latitudeSegments_ + 1);
				std::vector<float> cosY(latitudeSegments_ + 1);

				for (unsigned int x = 0; x <= longitudeSegments_; ++x) {
					float xSegment = static_cast<float>(x) / longitudeSegments_;
					float angleX = xSegment * twoPi;
					sinX[x] = std::sin(angleX);
					cosX[x] = std::cos(angleX);
				}

				for (unsigned int y = 0; y <= latitudeSegments_; ++y) {
					float ySegment = static_cast<float>(y) / latitudeSegments_;
					float angleY = ySegment * pi;
					sinY[y] = std::sin(angleY);
					cosY[y] = std::cos(angleY);
				}

				// Generate vertices and normals
				unsigned int vertexIndex = 0;
				for (unsigned int y = 0; y <= latitudeSegments_; ++y) {
					float sinY_val = sinY[y];
					float cosY_val = cosY[y];
					for (unsigned int x = 0; x <= longitudeSegments_; ++x) {
						float sinX_val = sinX[x];
						float cosX_val = cosX[x];

						// Calculate position using radius_
						float posX = radius_ * cosX_val * sinY_val;
						float posY = radius_ * cosY_val;
						float posZ = radius_ * sinX_val * sinY_val;

						// Normal vector (normalize position vector for the normal)
						float nx = cosX_val * sinY_val;
						float ny = cosY_val;
						float nz = sinX_val * sinY_val;

						// Position
						vertices_[vertexIndex++] = posX;
						vertices_[vertexIndex++] = posY;
						vertices_[vertexIndex++] = posZ;

						// Normal
						vertices_[vertexIndex++] = nx;
						vertices_[vertexIndex++] = ny;
						vertices_[vertexIndex++] = nz;
					}
				}

				// Generate indices (same as before)
				unsigned int index = 0;
				for (unsigned int y = 0; y < latitudeSegments_; ++y) {
					unsigned int base = y * (longitudeSegments_ + 1);
					unsigned int nextBase = (y + 1) * (longitudeSegments_ + 1);
					if ((y & 1) == 0) { // even rows
						for (unsigned int x = 0; x <= longitudeSegments_; ++x) {
							indices_[index++] = base + x;
							indices_[index++] = nextBase + x;
						}
					}
					else { // odd rows
						for (int x = longitudeSegments_; x >= 0; --x) {
							indices_[index++] = nextBase + x;
							indices_[index++] = base + x;
						}
					}
				}
			}



            const std::vector<GLfloat>& Sphere::getVertices() const {
                return vertices_;
            }

            const std::vector<GLuint>& Sphere::getIndices() const {
                return indices_;
            }

			void Sphere::initialize() {
				// Generate and bind VAO, VBO, and EBO
				VAO_.generate();
				VBO_.generate();
				EBO_.generate();

				VAO_.bind();

				// Upload vertex and index data to GPU
				VBO_.set_data(vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
				EBO_.set_data(indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

				// Link the position attribute (location = 0)
				// Each vertex consists of 6 floats: 3 for position, 3 for normal
				VAO_.link_attrib(
					VBO_,				    // VBO
					0,                    // Attribute location in the shader
					3,                    // Number of components (x, y, z)
					GL_FLOAT,             // Data type
					6 * sizeof(GLfloat),  // Stride (total size of a vertex)
					(void*)0,             // Offset (start of position data)
					GL_FALSE              // Normalized
				);

				// Link the normal attribute (location = 1)
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


            void Sphere::render() const {
                VAO_.bind();
                Gem::GL::draw_elements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, 0);
                VAO_.unbind();
            }

        } // namespace Shapes
    } // namespace Graphics
} // namespace Gem