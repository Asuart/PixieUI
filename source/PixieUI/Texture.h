#ifndef PIXIE_UI_TEXTURE
#define PIXIE_UI_TEXTURE

#include "Element.h"

namespace PixieUI {

	extern const Style defaultTextureStyle;

	class Texture : public Element {
	public:
		Texture(int32_t x, int32_t y, uint32_t width, uint32_t height, int32_t priority = 0, const Style& style = defaultTextureStyle);

		void UploadTexture(uint32_t width, uint32_t height, void* data, GLenum format, GLenum type);
		void Draw() override;

	protected:
		GLuint m_texture = 0;
		uint32_t m_textureWidth = 0;
		uint32_t m_textureHeight = 0;

		void CreateTexture();
	};

}

#endif // PIXIE_UI_TEXTURE