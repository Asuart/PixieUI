#ifndef PIXIE_UI_FRAME_BUFFER
#define PIXIE_UI_FRAME_BUFFER

#include <cstdint>
#include <glad/glad.h>

namespace PixieUI {

	struct FrameBuffer {
		FrameBuffer(uint32_t width, uint32_t height);
		~FrameBuffer();

		void Resize(uint32_t width, uint32_t height);
		void Bind();
		void Unbind();

		GLuint m_frameBuffer;
		GLuint m_colorAttachment, m_depthStencilAttachment;
		uint32_t m_width;
		uint32_t m_height;
	};

}

#endif // PIXIE_UI_FRAME_BUFFER