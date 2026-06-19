#ifndef PIXIE_UI_DYNAMIC_TEXTURE_SHADER
#define PIXIE_UI_DYNAMIC_TEXTURE_SHADER

namespace PixieUI {

	const char* const DYNAMIC_TEXTURE_VERTEX_SHADER =
		"#version 330 core\n"
		"layout(location = 0) in vec2 position;\n"
		"out vec2 fTexCoord;\n"
		"uniform vec2 uPos;\n"
		"uniform vec2 uSize;\n"
		"uniform vec2 uTexCoordStart;\n"
		"uniform vec2 uTexCoordSize;\n"
		"void main() {\n"
		"   fTexCoord = vec2(position.x, position.y) * uTexCoordSize + uTexCoordStart;\n"
		"	vec2 transformedPosition = vec2(position.x * uSize.x + uPos.x, -position.y * uSize.y - uPos.y) * 2.0 - vec2(1.0, -1.0);\n"
		"   gl_Position = vec4(transformedPosition, 0.0, 1.0);\n"
		"}\n";

	const char* const DYNAMIC_TEXTURE_FRAGMENT_SHADER =
		"#version 330 core\n"
		"out vec4 color;\n"
		"in vec2 fTexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"void main() {\n"
		"color = vec4(texture(ourTexture, fTexCoord).rgb, 1.0);\n"
		"}\n";

}

#endif // PIXIE_UI_DYNAMIC_TEXTURE_SHADER