#ifndef PIXIE_UI_BUTTON
#define PIXIE_UI_BUTTON

#include "Element.h"
#include "Style.h"

namespace PixieUI {

	extern const Style defaultButtonStyle;

	struct ButtonConfig {
		std::string text;
		std::function<bool(int32_t, int32_t)> clickCallback;
		ButtonConfig(const std::string& text, std::function<bool(int32_t, int32_t)> clickCallback = nullptr) : text(text), clickCallback(clickCallback) {}
	};

	class Button : public Element {
	public:
		Button(const ButtonConfig& config, int32_t x, int32_t y, int32_t priority = 0, const Style& style = defaultButtonStyle);

		void Draw() override;

	protected:
		std::string m_text = "";

		void UpdateSize();
	};

}

#endif // PIXIE_UI_BUTTON