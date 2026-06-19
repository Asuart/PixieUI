#include "Renderer.h"

using namespace PixieUI;

bool Renderer::m_initialized = false;
GLuint Renderer::m_screenPlaneVAO = 0;
GLuint Renderer::m_screenPlaneVBO = 0;
std::array<GLuint, (uint32_t)Shader::Count> Renderer::m_programs;
uint32_t Renderer::m_canvasWidth = 0;
uint32_t Renderer::m_canvasHeight = 0;
GLuint Renderer::m_fontTexture = 0;

bool Renderer::Init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programs[(uint32_t)Shader::FittedTexture] = ShaderLibrary::CreateShaderProgramm(
		FITTED_TEXTURE_VERTEX_SHADER,
		FITTED_TEXTURE_FRAGMENT_SHADER
	);

	m_programs[(uint32_t)Shader::Plane] = ShaderLibrary::CreateShaderProgramm(
		PLANE_VERTEX_SHADER,
		PLANE_FRAGMENT_SHADER
	);

	m_programs[(uint32_t)Shader::DynamicTexture] = ShaderLibrary::CreateShaderProgramm(
		DYNAMIC_TEXTURE_VERTEX_SHADER,
		DYNAMIC_TEXTURE_FRAGMENT_SHADER
	);

	m_programs[(uint32_t)Shader::Text] = ShaderLibrary::CreateShaderProgramm(
		TEXT_VERTEX_SHADER,
		TEXT_FRAGMENT_SHADER
	);

	const float vertexes[] = {
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0, 1.0, 0.0
	};

	glGenVertexArrays(1, &m_screenPlaneVAO);
	glBindVertexArray(m_screenPlaneVAO);

	glGenBuffers(1, &m_screenPlaneVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_screenPlaneVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, &m_fontTexture);
	glBindTexture(GL_TEXTURE_2D, m_fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	uint8_t* fontTexture = UnpackTexture(packedFontTexture);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA32F,
		packedFontTexture.width, packedFontTexture.height,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		fontTexture
	);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] fontTexture;

	m_initialized = true;
	return true;
}

bool Renderer::IsInitialized() {
	return m_initialized;
}

void Renderer::SetCanvasSize(uint32_t width, uint32_t height) {
	m_canvasWidth = width;
	m_canvasHeight = height;
}

void Renderer::DrawRect(int32_t x, int32_t y, uint32_t width, uint32_t height, Color color, uint32_t borderWidth, Color borderColor) {
	if (color.a == 0) return;
	GLuint program = GetProgram(Shader::Plane);
	GLuint posLoc = glGetUniformLocation(program, "uPos");
	GLuint sizeLoc = glGetUniformLocation(program, "uSize");
	GLuint colorLoc = glGetUniformLocation(program, "uColor");
	GLuint borderWidthLoc = glGetUniformLocation(program, "uBorderWidth");
	GLuint borderColorLoc = glGetUniformLocation(program, "uBorderColor");

	glUseProgram(program);
	glUniform2f(posLoc, (float)x / m_canvasWidth, (float)y / m_canvasHeight);
	glUniform2f(sizeLoc, (float)width / m_canvasWidth, (float)height / m_canvasHeight);
	glUniform4f(colorLoc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	glUniform4f(borderColorLoc, borderColor.r / 255.0f, borderColor.g / 255.0f, borderColor.b / 255.0f, borderColor.a / 255.0f);
	glUniform2f(borderWidthLoc, (float)borderWidth / width, (float)borderWidth / height);
	glBindVertexArray(m_screenPlaneVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}

void Renderer::DrawTexture(int32_t x, int32_t y, uint32_t width, uint32_t height, GLuint texture) {
	DrawTextureMapped(x, y, width, height, texture);
}

void Renderer::DrawTextureMapped(int32_t x, int32_t y, uint32_t width, uint32_t height, GLuint texture, float uOffset, float vOffset, float uSize, float vSize) {
	GLuint program = GetProgram(Shader::DynamicTexture);
	GLuint posLoc = glGetUniformLocation(program, "uPos");
	GLuint sizeLoc = glGetUniformLocation(program, "uSize");
	GLuint texCoordStartLoc = glGetUniformLocation(program, "uTexCoordStart");
	GLuint texCoordSizeLoc = glGetUniformLocation(program, "uTexCoordSize");

	glUseProgram(program);
	glUniform2f(posLoc, (float)x / m_canvasWidth, (float)y / m_canvasHeight);
	glUniform2f(sizeLoc, (float)width / m_canvasWidth, (float)height / m_canvasHeight);
	glUniform2f(texCoordStartLoc, uOffset, vOffset);
	glUniform2f(texCoordSizeLoc, uSize, vSize);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(m_screenPlaneVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::DrawText(const std::string& text, int32_t x, int32_t y, Color color, uint32_t maxWidth, uint32_t maxHeight) {
	(void)maxHeight;

	GLuint program = GetProgram(Shader::Text);
	GLuint posLoc = glGetUniformLocation(program, "uPos");
	GLuint sizeLoc = glGetUniformLocation(program, "uSize");
	GLuint texCoordStartLoc = glGetUniformLocation(program, "uTexCoordStart");
	GLuint texCoordSizeLoc = glGetUniformLocation(program, "uTexCoordSize");
	GLuint colorLoc = glGetUniformLocation(program, "uColor");

	glUseProgram(program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Renderer::GetFontTexture());
	glBindVertexArray(m_screenPlaneVAO);

	glUniform4f(colorLoc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

	uint32_t charsPerLine = 1000000;
	if(maxWidth > 0) charsPerLine = maxWidth / 8;
	//uint32_t lines = (uint32_t)ceil((float)text.size() / charsPerLine);

	for (uint32_t i = 0; i < text.size(); i++) {
		float offX = ((text[i] - 32) % 10) * 0.1f;
		float offY = floor((text[i] - 32) / 10.0f) * 0.1f;
		float sizeX = 1.0f / 10.0f;
		float sizeY = 1.0f / 10.0f;

		glUniform2f(posLoc, (float)(x + 3 + (i % charsPerLine) * 6) / m_canvasWidth, (float)(y + 3 + (i / charsPerLine) * 8) / m_canvasHeight);
		glUniform2f(sizeLoc, (float)6 / m_canvasWidth, (float)8 / m_canvasHeight);
		glUniform2f(texCoordStartLoc, offX, offY);
		glUniform2f(texCoordSizeLoc, sizeX, sizeY);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::DrawScreenPlane(GLuint textureID, uint32_t textureWidth, uint32_t textureHeight, uint32_t viewportWidth, uint32_t viewportHeight) {
	GLuint program = GetProgram(Shader::FittedTexture);
	GLuint posLoc = glGetUniformLocation(program, "uPos");
	GLuint sizeLoc = glGetUniformLocation(program, "uSize");

	float textureAspect = (float)textureWidth / textureHeight;
	float viewportAspect = (float)viewportWidth / viewportHeight;
	float posX, posY;
	float sizeX, sizeY;
	if (viewportAspect > textureAspect) {
		sizeY = 1.0f;
		sizeX = textureAspect / viewportAspect;
		posX = (1.0f - sizeX) * 0.5f;
		posY = 0.0f;
	}
	else {
		sizeX = 1.0f;
		sizeY = viewportAspect / textureAspect;
		posX = 0.0f;
		posY = (1.0f - sizeY) * 0.5f;
	}

	glUseProgram(program);
	glUniform2f(posLoc, posX, posY);
	glUniform2f(sizeLoc, sizeX, sizeY);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(m_screenPlaneVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

GLuint Renderer::GetFontTexture() {
	return m_fontTexture;
}

GLuint Renderer::GetProgram(Shader shader) {
	return m_programs[(uint32_t)shader];
}
