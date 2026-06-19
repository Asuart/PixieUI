#ifndef PIXIE_UI_LAYOUT
#define PIXIE_UI_LAYOUT

#include "Element.h"

namespace PixieUI {

	class Layout {
	public:
		Layout(uint32_t width, uint32_t height);
		~Layout();

		uint32_t GetWidth();
		uint32_t GetHeight();
		void AttachElement(Element* element);
		void RemoveElement(Element* element);
		void Draw();
		void SetCursorPosition(int32_t x, int32_t y);
		bool Click(int32_t x, int32_t y);
		bool Click();
		bool Scroll(int32_t x, int32_t y, int32_t value);
		bool Scroll(int32_t value);

	private:
		const uint32_t m_width;
		const uint32_t m_height;
		std::vector<Element*> m_children = std::vector<Element*>();
		Element* m_activeElement = nullptr;
		int32_t m_cursorX = 0;
		int32_t m_cursorY = 0;
	};

}

#endif // PIXIE_UI_LAYOUT