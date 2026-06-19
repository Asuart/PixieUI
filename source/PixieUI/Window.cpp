#include "Window.h"

using namespace PixieUI;

const Style PixieUI::defaultWindowOverlayStyle{
	Color(0, 0, 0, 180),
	Color(0, 0, 0, 180),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	0,
};

const Style PixieUI::defaultWindowBaseStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	1,
};

const Style PixieUI::defaultWindowButtonStyle{
	Color(0, 0, 0),
	Color(0, 0, 0),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	Color(255, 255, 255),
	1,
};

Window::Window(const std::string& title, uint32_t width, uint32_t height, Element* content, int32_t priority, const Style& overlayStyle, const Style& baseStyle, const Style& buttonStyle)
	: Element(0, 0, width, height, priority, overlayStyle), m_title(title) {
	Element* windowBase = new Element(10, 10, width - 20, height - 20, priority + 1, baseStyle);
	AddChild(windowBase);
	Element* windowCloseButton = new Button(
		ButtonConfig("X", [&](int32_t, int32_t) {
			this->Hide();
			return true;
			}
		), width - 25, 14, priority + 2, buttonStyle);
	windowBase->AddChild(windowCloseButton);
	Element* windowTitle = new Text(title, 0, 14, 0, 0, priority + 2, baseStyle);
	windowTitle->ForcePositionX(width / 2 - windowTitle->GetWidth() / 2);
	windowBase->AddChild(windowTitle);
	if (content) windowBase->AddChild(content);
	Hide();
}