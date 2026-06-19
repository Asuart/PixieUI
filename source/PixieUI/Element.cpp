#include "Element.h"

using namespace PixieUI;

const Style PixieUI::defaultElementStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	0,
};

Element::Element(int32_t x, int32_t y, uint32_t width, uint32_t height, int32_t priority, const Style& style)
	: m_x(x), m_y(y), m_width(width), m_height(height), m_priority(priority), m_style(style) {}

int32_t Element::GetPositionX() {
	return m_x;
}

int32_t Element::GetPositionY() {
	return m_y;
}

uint32_t Element::GetWidth() {
	return m_width;
}

uint32_t Element::GetHeight() {
	return m_height;
}

void Element::ForcePosition(int32_t x, int32_t y) {
	m_x = x;
	m_y = y;
}

void Element::ForcePositionX(int32_t x) {
	ForcePosition(x, m_y);
}

void Element::ForcePositionY(int32_t y) {
	ForcePosition(m_x, y);
}

void Element::ForceSize(uint32_t width, uint32_t height) {
	m_width = width;
	m_height = height;
}

void Element::ForceWidth(uint32_t width) {
	ForceSize(width, m_height);
}

void Element::ForceHeight(uint32_t height) {
	ForceSize(m_width, height);
}

bool Element::IsActive() {
	return m_active;
}

void Element::SetActive(bool state) {
	m_active = state;
}

Element* Element::GetParent() {
	return m_parent;
}

void Element::SetParent(Element* parent) {
	m_parent = parent;
}

void Element::AddChild(Element* el) {
	m_children.push_back(el);
}

void Element::Show() {
	if (m_hide & (uint8_t)HideFlags::self) {
		for (uint32_t i = 0; i < m_children.size(); i++) {
			m_children[i]->ShowRecoursive();
		}
	}
	bool wasHidden = m_hide;
	m_hide &= ~(uint8_t)HideFlags::self;
	if (m_showCallback && wasHidden && !m_hide) m_showCallback();
}

void Element::Hide() {
	if (!(m_hide & (uint8_t)HideFlags::self)) {
		for (uint32_t i = 0; i < m_children.size(); i++) {
			m_children[i]->HideRecoursive();
		}
	}
	bool wasHidden = m_hide;
	m_hide |= (uint8_t)HideFlags::self;
	if (m_hideCallback && !wasHidden && m_hide) m_hideCallback();
}

bool Element::IsHidden() {
	return m_hide;
}

void Element::ShowRecoursive() {
	m_hide &= ~(uint8_t)HideFlags::parent;
	if (m_hide & (uint8_t)HideFlags::self) return;
	if (m_showCallback) m_showCallback();
	for (uint32_t i = 0; i < m_children.size(); i++) {
		m_children[i]->ShowRecoursive();
	}
}

void Element::HideRecoursive() {
	m_hide |= (uint8_t)HideFlags::parent;
	if (m_hide & (uint8_t)HideFlags::self) return;
	if (m_hideCallback) m_hideCallback();
	for (uint32_t i = 0; i < m_children.size(); i++) {
		m_children[i]->HideRecoursive();
	}
}

void Element::Draw() {
	if (m_hide) return;
	if (m_active) {
		Renderer::DrawRect(m_x, m_y, m_width, m_height, m_style.bgActiveColor, m_style.borderWidth, m_style.borderActiveColor);
	}
	else {
		Renderer::DrawRect(m_x, m_y, m_width, m_height, m_style.bgColor, m_style.borderWidth, m_style.borderColor);
	}
}

void Element::SetClickCallback(std::function<bool(int32_t, int32_t)> clickCallback) {
	m_clickCallback = clickCallback;
}

bool Element::Click(int32_t x, int32_t y) {
	if (!m_clickCallback) return false;
	return m_clickCallback(x, y);
}

void Element::SetScrollCallback(std::function<bool(int32_t, int32_t, int32_t)> scrollCallback) {
	m_scrollCallback = scrollCallback;
}

bool Element::Scroll(int32_t x, int32_t y, int32_t value) {
	if (!m_scrollCallback) return false;
	return m_scrollCallback(x, y, value);
}

void Element::SetShowCallback(std::function<void()> showCallback) {
	m_showCallback = showCallback;
}

void Element::SetHideCallback(std::function<void()> hideCallback) {
	m_hideCallback = hideCallback;
}
