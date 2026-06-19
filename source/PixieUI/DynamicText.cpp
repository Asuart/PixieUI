#include "DynamicText.h"

using namespace PixieUI;

DynamicText::DynamicText(std::function<std::string()> getText, int32_t x, int32_t y, uint32_t maxWidth, uint32_t maxHeight, int32_t priority, const Style& style)
	: Element(x, y, 0, 0, priority, style), m_maxWidth(maxWidth), m_maxHeight(maxHeight), m_getText(getText) {
	std::string startupText = m_getText();
	UpdateSize(startupText);
}

void DynamicText::Draw() {
	if (m_hide) return;
	std::string text = m_getText();
	UpdateSize(text);
	Renderer::DrawText(text, m_x, m_y, m_active ? m_style.fontActiveColor : m_style.fontColor, m_maxWidth, m_maxHeight);
}

void DynamicText::UpdateSize(const std::string& text) {
	uint32_t charsPerLine = m_maxWidth / 8;
	uint32_t lines = (uint32_t)ceil((float)text.size() / charsPerLine);
	if (lines > 1) {
		m_width = charsPerLine * 6;
		m_height = lines * 8;
	}
	else {
		m_width = (uint32_t)text.size() * 6;
		m_height = 8;
	}
}