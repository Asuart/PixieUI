#include "BMPDecoder.h"

using namespace PixieUI;

BMP::BMP(uint8_t* buffer, uint32_t width, uint32_t height, uint8_t channels)
	: width(width), height(height), channels(channels) {
	data.resize(width * height * channels);
	for (uint32_t i = 0; i < width * height * channels; i++) {
		data[i] = buffer[i];
	}
}

BMP* PixieUI::LoadBMPFile(const std::string& path) {
	BMPFileHeader fileHeader;
	BMPInfoHeader infoHeader;
	BMPColorHeader colorHeader;

	std::ifstream reader = std::ifstream(path, std::ios::binary);
	if (!reader) {
		return nullptr;
	}

	reader.read((char*)&fileHeader, sizeof(fileHeader));
	if (fileHeader.marker != 0x4D42) {
		return nullptr;
	}

	reader.read((char*)&infoHeader, sizeof(infoHeader));
	if (infoHeader.bitCount == 32) {
		if (infoHeader.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
			reader.read((char*)&colorHeader, sizeof(colorHeader));
			BMPColorHeader expectedColorHeader;
			if (expectedColorHeader.redMask != colorHeader.redMask ||
				expectedColorHeader.blueMask != colorHeader.blueMask ||
				expectedColorHeader.greenMask != colorHeader.greenMask ||
				expectedColorHeader.alphaMask != colorHeader.alphaMask) {
				return nullptr;
			}
			if (expectedColorHeader.colorSpaceType != colorHeader.colorSpaceType) {
				return nullptr;
			}
		}
		else {
			return nullptr;
		}
	}

	reader.seekg(fileHeader.pixelOffset, reader.beg);

	uint32_t dataSize = infoHeader.imageWidth * infoHeader.imageHeight * infoHeader.bitCount / 8;
	uint8_t* data = new uint8_t[dataSize];

	uint32_t rowStride = infoHeader.imageWidth * infoHeader.bitCount / 8;
	uint8_t align = rowStride % 4;
	if (align) align = 4 - align;
	uint32_t newStride = rowStride + align;
	std::vector<uint8_t> paddingRow(newStride - rowStride);
	if (infoHeader.imageHeight < 0) {
		infoHeader.imageHeight = abs(infoHeader.imageHeight);
		for (int32_t y = infoHeader.imageHeight - 1; y >= 0; y--) {
			reader.read((char*)(data + rowStride * y), rowStride);
			reader.read((char*)paddingRow.data(), paddingRow.size());
		}
	}
	else {
		for (int32_t y = 0; y < infoHeader.imageHeight; y++) {
			reader.read((char*)(data + rowStride * (infoHeader.imageHeight - 1 - y)), rowStride);
			reader.read((char*)paddingRow.data(), paddingRow.size());
		}
	}

	return new BMP(data, infoHeader.imageWidth, infoHeader.imageHeight, static_cast<int8_t>(infoHeader.bitCount / 8));
}