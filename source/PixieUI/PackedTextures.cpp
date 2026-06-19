#include "PackedTextures.h"

using namespace PixieUI;

uint8_t* PixieUI::UnpackTexture(const PackedTexture& texture) {
	uint8_t* result = nullptr;
	uint32_t dataSize = 0;
	switch (texture.packing) {
	case TexturePacking::RunlengthGreyscale:
		if (texture.data.size() % 2) throw new std::exception("Packed texture is wrong.");
		dataSize = texture.width * texture.height * 3;
		result = new uint8_t[dataSize];
		for (size_t i = 0, j = 0; i < texture.data.size(); i += 2) {
			for (size_t k = 0; k < texture.data[i] * 3; k++, j++) {
				if (j >= dataSize) throw new std::exception("Packed texture is too big.");
				result[j] = texture.data[i + 1];
			}
		}
		break;
	case TexturePacking::Greyscale:
	default:
		if (texture.data.size() != texture.width * texture.height) throw new std::exception("Packed texture is wrong.");
		dataSize = (uint32_t)texture.data.size() * 3;
		result = new uint8_t[dataSize];
		for (size_t i = 0; i < texture.data.size(); i++) {
			result[i * 3] = texture.data[i];
			result[i * 3 + 1] = texture.data[i];
			result[i * 3 + 2] = texture.data[i];
		}
	}
	return result;
}
