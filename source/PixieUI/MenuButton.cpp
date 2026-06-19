#include "MenuButton.h"

using namespace PixieUI;

MenuButton::MenuButton(const MenuButtonConfig& config, int32_t x, int32_t y, int32_t priority, const Style& style, const Style& dropdownStyle, const Style& dropdownButtonStyle)
	: Button({ config.name, config.clickCallback }, x, y, priority, style) {
	if (config.dropdown.buttons.size()) {
		Element* dropdown = new ButtonList(config.dropdown, m_x, m_y + 13, priority + 1, dropdownStyle, dropdownButtonStyle);
		dropdown->SetParent(this);
		m_children.push_back(dropdown);
		dropdown->Hide();
	}
}

void MenuButton::SetActive(bool state) {
	m_active = state;
	if (!m_children.size()) return;
	if (state) m_children[0]->Show();
	else m_children[0]->Hide();
}