#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"


CTexture::CTexture(std::string filename)
{
	if (!readPNG(filename))
		exit(-1);
}


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}


ubyte4 CTexture::getTexel(int x, int y) const
{
	ubyte4 color(0, 0, 0, 0);
	uint8_t* pixelData = mvpData + (y * mWidth + x) * mChannels;

	color.b = *(pixelData + 0);
	color.g = *(pixelData + 1);
	color.r = *(pixelData + 2);
	if (mChannels == 4)
		color.a = *(pixelData + 3);

	return color;
}


ubyte4 CTexture::getTexel(float x, float y) const
{
	int xi = (x == 1.0f ? mWidth - 1 : int(x * float(mWidth)));
	int yi = (y == 1.0f ? mHeight - 1 : int(y * float(mHeight)));

	//  clamp, etc.?

	return getTexel(xi, yi);
}


void CTexture::setTexel(int x, int y, const ubyte4& color)
{
	uint8_t* pixelData = mvpData + (y * mWidth + x) * mChannels;

	*(pixelData + 0) = color.b;
	*(pixelData + 1) = color.g;
	*(pixelData + 2) = color.r;
	if (mChannels == 4)
		*(pixelData + 3) = color.a;
}


bool CTexture::readPNG(std::string filename)
{
	return (mvpData = stbi_load(filename.c_str(), &mWidth, &mHeight, &mChannels, 0)) != 0;
}


void CTexture::writePNG(std::string filename)
{
	stbi_write_png(filename.c_str(), mWidth, mHeight, mChannels, mvpData, (mChannels * mWidth + mChannels) & ~mChannels);
}
