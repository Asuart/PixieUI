#ifndef PIXIE_UI_RENDERER
#define PIXIE_UI_RENDERER

#include <cstdint>
#include <array>
#include <glad/glad.h>
#include "ShaderLibrary.h"
#include "BMPDecoder.h"
#include "Shaders.h"
#include "Color.h"
#include "Style.h"
#include "PackedTextures.h"

namespace PixieUI {

	class Renderer {
	public:
		Renderer() = delete;

		static bool Init();
		static bool IsInitialized();

		static void SetCanvasSize(uint32_t width, uint32_t height);
		static void DrawRect(int32_t x, int32_t y, uint32_t width, uint32_t height, Color color, uint32_t borderWidth = 0, Color borderColor = Color(0, 0, 0, 0));
		static void DrawTexture(int32_t x, int32_t y, uint32_t width, uint32_t height, GLuint texture);
		static void DrawTextureMapped(int32_t x, int32_t y, uint32_t width, uint32_t height, GLuint texture, float uOffset = 0.0, float vOffset = 0.0, float uSize = 1.0, float vSize = 1.0);
		static void DrawText(const std::string& text, int32_t x, int32_t y, Color color = Color(255, 255, 255), uint32_t maxWidth = 0, uint32_t maxHeight = 0);
		static void DrawScreenPlane(GLuint textureID, uint32_t textureWidth, uint32_t textureHeight, uint32_t viewportWidth, uint32_t viewportHeight);

		static GLuint GetFontTexture();
		static GLuint GetProgram(Shader shader);

	private:
		static bool m_initialized;
		static GLuint m_screenPlaneVAO;
		static GLuint m_screenPlaneVBO;
		static std::array<GLuint, (uint32_t)Shader::Count> m_programs;
		static uint32_t m_canvasWidth;
		static uint32_t m_canvasHeight;
		static GLuint m_fontTexture;
	};

}

#endif // PIXIE_UI_RENDERER