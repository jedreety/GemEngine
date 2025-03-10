#include <Gem/Graphics/buffer.h>

namespace Gem {
    namespace Graphics {

        // Constructor
        Buffer::Buffer(GLenum type) noexcept
            : type_(type) {
            // Buffer type is set; buffer is not yet generated
        }

        // Destructor
        Buffer::~Buffer() {
            cleanup(); // Ensure buffer is deleted upon destruction
        }

        // Generate the buffer object
        void Buffer::generate() {
            if (!is_generated_) {
                GL::gen_buffers(1, &ID_);
                if (ID_ == 0) {
                    std::cerr << "Failed to generate buffer." << std::endl;
                }
                else {
                    is_generated_ = true;
                }
            }
            else {
                std::cerr << "Buffer already generated." << std::endl;
            }
        }

        // Bind the buffer
        void Buffer::bind() const {
            if (is_generated_) {
                GL::bind_buffer(type_, ID_);
            }
            else {
                std::cerr << "Buffer not generated; cannot bind." << std::endl;
            }
        }

        // Unbind the buffer
        void Buffer::unbind() const {
            GL::bind_buffer(type_, 0);
        }

        // Upload data to the buffer
        void Buffer::set_data(GLsizeiptr size, const void* data, GLenum usage) {
            if (is_generated_) {
                GL::bind_buffer(type_, ID_);
                GL::buffer_data(type_, size, data, usage);
                // Do not unbind here
            }
            else {
                std::cerr << "Buffer not generated; cannot set data." << std::endl;
            }
        }

        // Delete the buffer object
        void Buffer::cleanup() {
            if (is_generated_) {
                GL::delete_buffers(1, &ID_);
                ID_ = 0;
                is_generated_ = false;
            }
        }

        // Get the buffer ID
        [[nodiscard]] GLuint Buffer::get_ID() const noexcept {
            return ID_;
        }

        // Get the buffer type
        [[nodiscard]] GLenum Buffer::get_type() const noexcept {
            return type_;
        }

        // Set the buffer type before generation
        void Buffer::set_type(GLenum type) {
            if (!is_generated_) {
                type_ = type;
            }
            else {
                std::cerr << "Cannot change buffer type after generation." << std::endl;
            }
        }

        // Equality operator - compares buffer IDs and types
        bool Buffer::operator==(const Buffer& other) const noexcept {
            // Two buffers are equal if they have the same ID and type
            return (ID_ == other.ID_) && (type_ == other.type_);
        }

        // Inequality operator
        bool Buffer::operator!=(const Buffer& other) const noexcept {
            return !(*this == other);
        }

    } // namespace GL
} // namespace Gem
