#ifndef PIXIE_UI_MENU_BUTTON
#define PIXIE_UI_MENU_BUTTON

#include "Button.h"
#include "ButtonList.h"

namespace PixieUI {

	struct MenuButtonConfig {
		std::string name;
		std::function<bool(int32_t, int32_t)> clickCallback;
		ButtonListConfig dropdown;
		MenuButtonConfig(const std::string& name, std::function<bool(int32_t, int32_t)> clickCallback = nullptr, const ButtonListConfig& dropdown = ButtonListConfig({})) : name(name), clickCallback(clickCallback), dropdown(dropdown) {}
	};

	class MenuButton : public Button {
	public:
		MenuButton(const MenuButtonConfig& config, int32_t x, int32_t y, int32_t priority = 0, const Style& style = defaultButtonStyle, const Style& dropdownStyle = defaultButtonListStyle, const Style& dropdownButtonStyle = defaultButtonStyle);

		void SetActive(bool state) override;
	};

}

#endif // PIXIE_UI_MENU_BUTTON