#include "Text.h"

using namespace PixieUI;

const Style PixieUI::defaultTextStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	0,
};

Text::Text(const std::string& text, int32_t x, int32_t y, uint32_t maxWidth, uint32_t maxHeight, int32_t priority, const Style& style)
	: Element(x, y, 0, 0, priority, style), m_text(text), m_maxWidth(maxWidth), m_maxHeight(maxHeight) {
	UpdateSize();
}

void Text::Draw() {
	if (m_hide) return;
	Renderer::DrawText(m_text, m_x, m_y, m_active ? m_style.fontActiveColor : m_style.fontColor, m_maxWidth, m_maxHeight);
}

void Text::UpdateSize() {
	uint32_t charsPerLine = m_maxWidth / 8;
	uint32_t lines = (uint32_t)ceil((float)m_text.size() / charsPerLine);
	if (lines > 1) {
		m_width = charsPerLine * 6;
		m_height = lines * 8;
	}
	else {
		m_width = (uint32_t)m_text.size() * 6;
		m_height = 8;
	}
}