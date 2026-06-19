#ifndef PIXIE_UI_MENU
#define PIXIE_UI_MENU

#include <vector>
#include "MenuButton.h"

namespace PixieUI {

	extern const Style defaultMenuStyle;

	struct MenuConfig {
		std::vector<MenuButtonConfig> buttons;
		MenuConfig(const std::vector<MenuButtonConfig>& buttons) : buttons(buttons) {}
	};

	class Menu : public Element {
	public:
		Menu(const MenuConfig& config, int32_t x, int32_t y, uint32_t width, int32_t priority = 0, const Style& style = defaultMenuStyle, const Style& menuButtonStyle = defaultButtonStyle, const Style& dropdownStyle = defaultButtonListStyle, const Style& dropdownButtonStyle = defaultButtonStyle);

		void Draw() override;
	};

}

#endif // PIXIE_UI_MENU