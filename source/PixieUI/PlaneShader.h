#ifndef PIXIE_UI_PLANE_SHADER
#define PIXIE_UI_PLANE_SHADER

namespace PixieUI {

	const char* const PLANE_VERTEX_SHADER =
		"#version 330 core\n"
		"layout(location = 0) in vec2 position;\n"
		"out vec2 fTexCoord;\n"
		"uniform vec2 uPos;\n"
		"uniform vec2 uSize;\n"
		"void main() {\n"
		"	fTexCoord = vec2(position.x, position.y);\n"
		"	vec2 transformedPosition = vec2(position.x * uSize.x + uPos.x, -position.y * uSize.y - uPos.y) * 2.0 - vec2(1.0, -1.0);\n"
		"   gl_Position = vec4(transformedPosition, 0.0, 1.0);\n"
		"}\n";

	const char* const PLANE_FRAGMENT_SHADER =
		"#version 330 core\n"
		"out vec4 color;\n"
		"in vec2 fTexCoord;\n"
		"uniform vec4 uColor;\n"
		"uniform vec4 uBorderColor;\n"
		"uniform vec2 uBorderWidth;\n"
		"void main() {\n"
		"	if(fTexCoord.x > uBorderWidth.x && (1.0f - fTexCoord.x) > uBorderWidth.x && fTexCoord.y > uBorderWidth.y && (1.0f - fTexCoord.y) > uBorderWidth.y) color = uColor;\n"
		"	else color = uBorderColor;\n"
		"}\n";

}

#endif // PIXIE_UI_PLANE_SHADER