#include "Color.h"

using namespace PixieUI;

Color::Color(int32_t r, int32_t g, int32_t b, int32_t a) :
	r(uint8_t(r)), g(uint8_t(g)), b(uint8_t(b)), a(uint8_t(a)) {}

Color::Color(float r, float g, float b, float a) :
	r(uint8_t(r * 255)), g(uint8_t(g * 255)), b(uint8_t(b * 255)), a(uint8_t(a * 255)) {}

Color::Color(double r, double g, double b, double a) :
	r(uint8_t(r * 255)), g(uint8_t(g * 255)), b(uint8_t(b * 255)), a(uint8_t(a * 255)) {}
