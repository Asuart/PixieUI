#include "Menu.h"

using namespace PixieUI;

const Style PixieUI::defaultMenuStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	0,
};

Menu::Menu(const MenuConfig& config, int32_t x, int32_t y, uint32_t width, int32_t priority, const Style& style, const Style& menuButtonStyle, const Style& dropdownStyle, const Style& dropdownButtonStyle)
	: Element(x, y, width, 16, priority, style) {
	int32_t startX = 1;
	for (size_t i = 0; i < config.buttons.size(); i++) {
		Element* btn = new MenuButton(config.buttons[i], m_x + startX, m_y + 1, m_priority + 1, menuButtonStyle, dropdownStyle, dropdownButtonStyle);
		btn->SetParent(this);
		m_children.push_back(btn);
		startX += btn->GetWidth() + 1;
	}
}

void Menu::Draw() {
	if (m_hide) return;
	Renderer::DrawRect(m_x, m_y, m_width, m_height, m_active ? m_style.bgActiveColor : m_style.bgColor);
}