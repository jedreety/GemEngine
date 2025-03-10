#pragma once

#include <../../GemCore/include-protected/function_overload.h>
#include <Gem/Graphics/buffer.h>
#include <Gem/Graphics/vao.h>
#include <vector>

namespace Gem {
    namespace Graphics {
        namespace Shapes {

            /**
             * @class Cube
             * @brief Represents a 3D cube shape with vertex and index data.
             */
            class Cube {

            public:

                /**
                 * @brief Constructs a Cube object with specified size.
                 * @param size The size (length of each side) of the cube.
                 */
                Cube(float size = 1.0f);
                ~Cube();

                /**
                 * @brief Retrieves the vertex data for the cube.
                 * @return A vector of floats representing vertex positions, normals, and texture coordinates.
                 */
                const std::vector<GLfloat>& getVertices() const;

                /**
                 * @brief Retrieves the index data for the cube.
                 * @return A vector of unsigned integers representing indices.
                 */
                const std::vector<GLuint>& getIndices() const;
                
                /**
                * @brief Renders the cube.
                */
                void render() const;
                
                private:
                
                /**
                    * @brief Initializes OpenGL buffers for the cube.
                    */
                void initialize();
                
                /**
                * @brief Generates vertex and index data for the cube.
                 */
                void generateData();

            private:

                float size_;

                std::vector<GLfloat> vertices_;
                std::vector<GLuint> indices_;

                Gem::Graphics::VAO VAO_;
                Gem::Graphics::Buffer VBO_, EBO_;

            };

        } // namespace Shapes
    } // namespace Graphics
} // namespace Gem