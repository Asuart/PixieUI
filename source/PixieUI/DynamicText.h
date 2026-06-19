#ifndef PIXIE_UI_DYNAMIC_TEXT
#define PIXIE_UI_DYNAMIC_TEXT

#include "Element.h"
#include "Text.h"

namespace PixieUI {

	class DynamicText : public Element {
	public:
		DynamicText(std::function<std::string()> getText, int32_t x, int32_t y, uint32_t maxWidth = 0, uint32_t maxHeight = 0, int32_t priority = 0, const Style& style = defaultTextStyle);

		void Draw() override;

	private:
		std::function<std::string()> m_getText;
		uint32_t m_maxWidth;
		uint32_t m_maxHeight;

		void UpdateSize(const std::string& text);
	};
}

#endif // PIXIE_UI_DYNAMIC_TEXT