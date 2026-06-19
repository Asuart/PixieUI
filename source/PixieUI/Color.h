#ifndef PIXIE_UI_COLOR
#define PIXIE_UI_COLOR

#include <cstdint>

namespace PixieUI {

	struct Color {
		uint8_t r, g, b, a;

		Color(int32_t r = 0, int32_t g = 0, int32_t b = 0, int32_t a = 255);
		Color(float r, float g, float b, float a = 1.0);
		Color(double r, double g, double b, double a = 1.0);
	};

}

#endif // PIXIE_UI_COLOR