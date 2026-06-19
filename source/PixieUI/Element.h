#ifndef PIXIE_UI_ELEMENT
#define PIXIE_UI_ELEMENT

#include <functional>
#include "Renderer.h"

namespace PixieUI {

	extern const Style defaultElementStyle;

	enum class HideFlags : uint8_t {
		self = 0b1,
		parent = 0b10
	};

	class Element {
	public:
		Element(int32_t x, int32_t y, uint32_t width, uint32_t height, int32_t priority = 0, const Style& style = defaultElementStyle);

		int32_t GetPositionX();
		int32_t GetPositionY();
		uint32_t GetWidth();
		uint32_t GetHeight();
		void ForcePosition(int32_t x, int32_t y);
		void ForcePositionX(int32_t x);
		void ForcePositionY(int32_t y);
		void ForceSize(uint32_t width, uint32_t height);
		void ForceWidth(uint32_t width);
		void ForceHeight(uint32_t height);
		bool IsActive();
		virtual void SetActive(bool state);
		Element* GetParent();
		void SetParent(Element* parent);
		void AddChild(Element* el);
		virtual void Show();
		virtual void Hide();
		bool IsHidden();
		void SetClickCallback(std::function<bool(int32_t, int32_t)> clickCallback);
		bool Click(int32_t x, int32_t y);
		void SetScrollCallback(std::function<bool(int32_t, int32_t, int32_t)> scrollCallback);
		bool Scroll(int32_t x, int32_t y, int32_t value);
		void SetShowCallback(std::function<void()> showCallback);
		void SetHideCallback(std::function<void()> hideCallback);

		virtual void Draw();

	protected:
		Element* m_parent = nullptr;
		std::vector<Element*> m_children = std::vector<Element*>();
		const Style& m_style;
		int32_t m_x;
		int32_t m_y;
		uint32_t m_width;
		uint32_t m_height;
		int32_t m_priority;
		bool m_active = false;
		uint8_t m_hide = false;
		std::function<bool(int32_t, int32_t)> m_clickCallback = nullptr;
		std::function<bool(int32_t, int32_t, int32_t)> m_scrollCallback = nullptr;
		std::function<void()> m_showCallback;
		std::function<void()> m_hideCallback;

		virtual void ShowRecoursive();
		virtual void HideRecoursive();

		friend class Layout;
		friend class Window;
	};

}

#endif // PIXIE_UI_ELEMENT