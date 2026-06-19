#ifndef PIXIE_UI
#define PIXIE_UI

#include "PackedTextures.h"
#include "FrameBuffer.h"
#include "ShaderLibrary.h"
#include "Color.h"
#include "Style.h"
#include "BMPDecoder.h"
#include "Shaders.h"
#include "Renderer.h"
#include "Element.h"
#include "Text.h"
#include "DynamicText.h"
#include "Texture.h"
#include "Layout.h"
#include "Button.h"
#include "ButtonList.h"
#include "MenuButton.h"
#include "Menu.h"
#include "Window.h"

namespace PixieUI {

	static inline bool Init() {
		return Renderer::Init();
	}

	static inline void SetCanvasSize(uint32_t width, uint32_t height) {
		Renderer::SetCanvasSize(width, height);
	}

}

#endif // PIXIE_UI