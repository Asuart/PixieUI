#include "ButtonList.h"

using namespace PixieUI;

const Style PixieUI::defaultButtonListStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	1,
};

ButtonList::ButtonList(const ButtonListConfig& config, int32_t x, int32_t y, int32_t priority, const Style& style, const Style& buttonStyle)
	: Element(x, y, 0, (uint32_t)config.buttons.size() * 15 + 5, priority, style) {
	for (size_t i = 0; i < config.buttons.size(); i++) {
		Element* btn = new Button(config.buttons[i], x + 3, y + 3 + (uint32_t)i * 15, priority + 1, buttonStyle);
		btn->SetParent(this);
		m_children.push_back(btn);
	}
	uint32_t maxWidth = 0;
	for (size_t i = 0; i < m_children.size(); i++) {
		if (m_children[i]->GetWidth() > maxWidth) maxWidth = m_children[i]->GetWidth();
	}
	m_width = maxWidth + 6;

	for (size_t i = 0; i < m_children.size(); i++) {
		m_children[i]->ForceWidth(maxWidth);
	}
}