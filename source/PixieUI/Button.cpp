#include "Button.h"

using namespace PixieUI;

const Style PixieUI::defaultButtonStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	1,
};

Button::Button(const ButtonConfig& config, int32_t x, int32_t y, int32_t priority, const Style& style)
	: Element(x, y, 0, 13, priority, style), m_text(config.text) {
	SetClickCallback(config.clickCallback);
	UpdateSize();
}

void Button::Draw() {
	if (m_hide) return;
	if (m_active) {
		Renderer::DrawRect(m_x, m_y, m_width, m_height, m_style.bgActiveColor, m_style.borderWidth, m_style.borderActiveColor);
		if (m_style.borderWidth) Renderer::DrawText(m_text, m_x, m_y, m_style.fontActiveColor);
	}
	else {
		Renderer::DrawRect(m_x, m_y, m_width, m_height, m_style.bgColor, m_style.borderWidth, m_style.borderColor);
		if (m_style.borderWidth) Renderer::DrawText(m_text, m_x, m_y, m_style.fontColor);
	}
}

void Button::UpdateSize() {
	m_width = (uint32_t)m_text.length() * 6 + 5;
}