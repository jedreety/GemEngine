#include <Gem/Graphics/textures/texture.h>

namespace Gem {

	namespace Graphics {

		// Destructor
		Texture::~Texture() {
			if (texture_ID_ != 0) {
				GL::delete_textures(1, &texture_ID_);
				texture_ID_ = 0;
			}
		}

		// Sets the path to the texture folder
		void Texture::set_path(const std::string& path) {
			path_ = path;
		}

		// Gets the texture ID
		[[nodiscard]] GLuint Texture::get_texture_ID() const noexcept {
			return texture_ID_;
		}

		// Generates the texture
		void Texture::generate() {
			GL::gen_textures(1, &texture_ID_);
			if (texture_ID_ == 0) {
				std::cerr << "ERROR::Texture::generate: Failed to generate texture." << std::endl;
				throw std::runtime_error("Failed to generate texture.");
			}
		}

		// Default implementation for set_wrap_r (optional, as not all textures use R coordinate)
		void Texture::set_wrap_r(GLint /*param*/) {
			// Do nothing by default
		}

	} // namespace Graphics

} // namespace Gem
