#include "Texture.h"

using namespace PixieUI;

const Style PixieUI::defaultTextureStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	0,
};

Texture::Texture(int32_t x, int32_t y, uint32_t width, uint32_t height, int32_t priority, const Style& style)
	: Element(x, y, width, height, priority, style) {}

void Texture::UploadTexture(uint32_t width, uint32_t height, void* data, GLenum format, GLenum type) {
	if (!m_texture) CreateTexture();
	m_textureWidth = width;
	m_textureHeight = height;
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB32F,
		width, height,
		0, format, type,
		data
	);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Draw() {
	if (m_hide) return;
	Renderer::DrawTextureMapped(m_x, m_y, m_width, m_height, m_texture);
}

void Texture::CreateTexture() {
	if (!m_texture) {
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}