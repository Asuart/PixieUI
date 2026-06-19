#ifndef PIXIE_UI_WINDOW
#define PIXIE_UI_WINDOW

#include "Button.h"
#include "Text.h"

namespace PixieUI {

	extern const Style defaultWindowOverlayStyle;
	extern const Style defaultWindowBaseStyle;
	extern const Style defaultWindowButtonStyle;

	class Window : public Element {
	public:
		Window(const std::string& title, uint32_t width, uint32_t height, Element* content = nullptr, int32_t priority = 0, const Style& overlayStyle = defaultWindowOverlayStyle, const Style& baseStyle = defaultWindowBaseStyle, const Style& buttonStyle = defaultWindowButtonStyle);

	private:
		const std::string m_title;
	};

}

#endif // PIXIE_UI_WINDOW