#ifndef PIXIE_UI_TEXT
#define PIXIE_UI_TEXT

#include "Element.h"

namespace PixieUI {

	extern const Style defaultTextStyle;

	class Text : public Element {
	public:
		Text(const std::string& text, int32_t x, int32_t y, uint32_t maxWidth = 0, uint32_t maxHeight = 0, int32_t priority = 0, const Style& style = defaultTextStyle);

		virtual void Draw() override;

	protected:
		std::string m_text;
		uint32_t m_maxWidth;
		uint32_t m_maxHeight;

		void UpdateSize();
	};

}

#endif // PIXIE_UI_TEXT