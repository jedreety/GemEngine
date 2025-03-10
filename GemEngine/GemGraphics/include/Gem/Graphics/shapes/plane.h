#pragma once

#include <../../GemCore/include-protected/function_overload.h>
#include <Gem/Graphics/buffer.h>
#include <Gem/Graphics/vao.h>
#include <vector>

namespace Gem {
    namespace Graphics {
        namespace Shapes {

            /**
             * @class Plane
             * @brief Represents a 3D plane shape with vertex and index data.
             */
            class Plane {

            public:

                /**
                 * @brief Constructs a Plane object with specified width and height.
                 * @param width The width of the plane.
                 * @param height The height of the plane.
                 * @param segments The number of segments in each dimension (for higher detail).
                 */
                Plane(float width = 1.0f, float height = 1.0f, unsigned int segments = 1);
                ~Plane();

                /**
                 * @brief Retrieves the vertex data for the plane.
                 * @return A vector of floats representing vertex positions, normals, and texture coordinates.
                 */
                const std::vector<GLfloat>& getVertices() const;

                /**
                 * @brief Retrieves the index data for the plane.
                 * @return A vector of unsigned integers representing indices.
                 */
                const std::vector<GLuint>& getIndices() const;
                
                /**
                * @brief Renders the plane.
                */
                void render() const;
                
                private:
                
                                /**
                                 * @brief Initializes OpenGL buffers for the plane.
                                 */
                                void initialize();
                
                /**
                 * @brief Generates vertex and index data for the plane.
                 */
                void generateData();

            private:

                float width_;
                float height_;
                unsigned int segments_;

                std::vector<GLfloat> vertices_;
                std::vector<GLuint> indices_;

                Gem::Graphics::VAO VAO_;
                Gem::Graphics::Buffer VBO_, EBO_;

            };

        } // namespace Shapes
    } // namespace Graphics
} // namespace Gem