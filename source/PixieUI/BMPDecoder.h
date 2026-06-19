#ifndef PIXIE_UI_BMP_DECODER
#define PIXIE_UI_BMP_DECODER

#include <fstream>
#include <vector>

namespace PixieUI {

#pragma pack(push, 1)
	struct BMPFileHeader {
		uint16_t marker;
		uint32_t fileSize;
		uint16_t reserved0;
		uint16_t reserved1;
		uint32_t pixelOffset;
	};

	struct BMPInfoHeader {
		uint32_t size;
		int32_t imageWidth;
		int32_t imageHeight;
		uint16_t planes;
		uint16_t bitCount;
		uint32_t compression;
		uint32_t sizeImage;
		int32_t xPPM;
		int32_t yPPM;
		uint32_t colorsUsed;
		uint32_t colorsImportant;
	};

	struct BMPColorHeader {
		uint32_t redMask = 0x00ff0000;
		uint32_t greenMask = 0x0000ff00;
		uint32_t blueMask = 0x000000ff;
		uint32_t alphaMask = 0xff000000;
		uint32_t colorSpaceType = 0x73524742;
		uint32_t unused[16] = { 0 };
	};
#pragma pack(pop)

	struct BMP {
		std::vector<uint8_t> data;
		uint32_t width;
		uint32_t height;
		uint8_t channels;

		BMP(uint8_t* buffer, uint32_t width, uint32_t height, uint8_t channels);
	};

	BMP* LoadBMPFile(const std::string& path);

}

#endif // PIXIE_UI_BMP_DECODER