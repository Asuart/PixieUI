#ifndef PIXIE_UI_SHADERS
#define PIXIE_UI_SHADERS

#include <cstdint>
#include "DynamicTextureShader.h"
#include "PlaneShader.h"
#include "FittedTextureShader.h"
#include "TextShader.h"

namespace PixieUI {

	enum class Shader : uint32_t {
		FittedTexture = 0,
		Plane,
		DynamicTexture,
		Text,
		Count
	};

}

#endif // PIXIE_UI_SHADERS