#ifndef PIXIE_UI_BUTTON_LIST
#define PIXIE_UI_BUTTON_LIST

#include "Element.h"
#include "Button.h"

namespace PixieUI {

	extern const Style defaultButtonListStyle;

	struct ButtonListConfig {
		std::vector<ButtonConfig> buttons;
		ButtonListConfig(const std::vector<ButtonConfig>& buttons) : buttons(buttons) {}
	};

	class ButtonList : public Element {
	public:
		ButtonList(const ButtonListConfig& config, int32_t x, int32_t y, int32_t priority = 0, const Style& style = defaultButtonListStyle, const Style& buttonStyle = defaultButtonStyle);
		~ButtonList();
	};

}

#endif // PIXIE_UI_BUTTON_LIST 