#include "Layout.h"

using namespace PixieUI;

Layout::Layout(uint32_t width, uint32_t height)
	: m_width(width), m_height(height) {}

Layout::~Layout() {
	for (size_t i = 0; i < m_children.size(); i++) {
		delete m_children[i];
	}
}

uint32_t Layout::GetWidth() {
	return m_width;
}

uint32_t Layout::GetHeight() {
	return m_height;
}

void Layout::AttachElement(Element* element) {
	m_children.push_back(element);
	for (uint32_t i = 0; i < element->m_children.size(); i++) {
		AttachElement(element->m_children[i]);
	}
}

void Layout::RemoveElement(Element* element) {
	for (uint32_t i = 0; i < m_children.size(); i++) {
		if (m_children[i] == element) {
			m_children.erase(m_children.begin() + i);
			for (uint32_t j = 0; j < element->m_children.size(); j++) {
				RemoveElement(element->m_children[j]);
			}
			break;
		}
	}
}

void Layout::Draw() {
	for (Element* child : m_children) {
		if (child->IsHidden()) continue;
		child->Draw();
	}
}

void Layout::SetCursorPosition(int32_t x, int32_t y) {
	// Save last cursor position for Click and Scroll events.
	m_cursorX = x;
	m_cursorY = y;

	// Elements with highest priorities are always at the end, so search is started from the end.
	// Once element is found, it and all it's parent are marked as active and search ends.
	Element* activeElement = nullptr;
	for (size_t i = 0; i < m_children.size(); i++) {
		size_t ri = m_children.size() - i - 1;
		if (m_children[ri]->IsHidden()) continue;
		if (x >= m_children[ri]->GetPositionX() && x < (int32_t)(m_children[ri]->GetPositionX() + m_children[ri]->GetWidth()) &&
			y >= m_children[ri]->GetPositionY() && y < (int32_t)(m_children[ri]->GetPositionY() + m_children[ri]->GetHeight())) {
			activeElement = m_children[ri];
			Element* el = activeElement;
			while (el) {
				el->SetActive(true);
				el = el->GetParent();
			}
			break;
		}
	}

	// If element is found, we try to find it's closest intersection in hierarchy with previous active elemetn.
	// Each time we got to previous element's parent, we mark that element as not active.
	// Otherwise we mark previous active element and all it's parents as not active.
	if (activeElement) {
		Element* oldRoot = m_activeElement;
		while (oldRoot) {
			Element* newRoot = activeElement;
			while (newRoot) {
				if (newRoot == oldRoot) {
					m_activeElement = activeElement;
					return;
				}
				newRoot = newRoot->GetParent();
			}
			oldRoot->SetActive(false);
			oldRoot = oldRoot->GetParent();
		}
	}
	else {
		Element* el = m_activeElement;
		while (el) {
			el->SetActive(false);
			el = el->GetParent();
		}
	}

	m_activeElement = activeElement;
}

bool Layout::Click(int32_t x, int32_t y) {
	SetCursorPosition(x, y);
	return Click();
}

bool Layout::Click() {
	if (!m_activeElement) return false;
	Element* el = m_activeElement;
	while (el) {
		if (el->Click(m_cursorX - el->m_x, m_cursorY - el->m_y)) return true;
		el = el->m_parent;
	}
	return false;
}

bool Layout::Scroll(int32_t x, int32_t y, int32_t value) {
	SetCursorPosition(x, y);
	return Scroll(value);
}

bool Layout::Scroll(int32_t value) {
	if (!m_activeElement) return false;
	Element* el = m_activeElement;
	while (el) {
		if (el->Scroll(m_cursorX - el->m_x, m_cursorY - el->m_y, value)) return true;
		el = el->m_parent;
	}
	return false;
}