#include <Gem/Graphics/vao.h>

namespace Gem {
    namespace Graphics {

        // Constructor
        VAO::VAO() noexcept {
            // VAO is not yet generated.
        }

        // Destructor
        VAO::~VAO() {
            cleanup(); // Ensure the VAO is deleted upon destruction.
        }

        // Generate the VAO
        void VAO::generate() {
            if (!is_generated_) {
                GL::gen_vertex_arrays(1, &ID_);
                if (ID_ == 0) {
                    std::cerr << "Failed to generate VAO." << std::endl;
                }
                else {
                    is_generated_ = true;
                }
            }
            else {
                std::cerr << "VAO already generated." << std::endl;
            }
        }

        // Bind the VAO
        void VAO::bind() const {
            if (is_generated_) {
                GL::bind_vertex_array(ID_);
            }
            else {
                std::cerr << "VAO not generated; cannot bind." << std::endl;
            }
        }

        // Unbind the VAO
        void VAO::unbind() const {
            GL::bind_vertex_array(0);
        }

        // Link a VBO to the VAO
        void VAO::link_attrib(const Buffer& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, const void* offset, GLboolean normalized) {
            // Bind the VBO (vertex buffer object)
            VBO.bind();

            // Bind the VAO
            bind();

            // Set the vertex attribute pointer
            GL::vertex_attrib_pointer(layout, numComponents, type, normalized, stride, offset);

            // Enable the vertex attribute array
            GL::enable_vertex_attrib_array(layout);

            // Unbind the VBO
            VBO.unbind();

            // Optionally unbind ( Make the program crash )
            // unbind();
        }

        // Delete the VAO
        void VAO::cleanup() {
            if (is_generated_) {
                GL::delete_vertex_arrays(1, &ID_);
                ID_ = 0;
                is_generated_ = false;
            }
        }

        // Get the VAO ID
        [[nodiscard]] GLuint VAO::get_ID() const noexcept {
            return ID_;
        }

        // Equality operator
        bool VAO::operator==(const VAO& other) const noexcept {
            return ID_ == other.ID_;
        }

        // Inequality operator
        bool VAO::operator!=(const VAO& other) const noexcept {
            return !(*this == other);
        }

    } // namespace GL
} // namespace Gem
