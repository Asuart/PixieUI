#ifndef PIXIE_UI_STYLE
#define PIXIE_UI_STYLE

#include "Color.h"

namespace PixieUI {

	struct Style {
		Color bgColor = Color(0, 0, 0);
		Color bgActiveColor = Color(0, 0, 0);
		Color fontColor = Color(255, 255, 255);
		Color fontActiveColor = Color(180, 255, 180);
		Color borderColor = Color(255, 255, 255);
		Color borderActiveColor = Color(180, 255, 180);
		uint32_t borderWidth = 0;
	};
}

#endif // PIXIE_UI_STYLE