#pragma once

#include <cstdint>
#include <string>

#include "../jmath/jmath.h"


class CTexture
{
private:
	int mWidth, mHeight, mChannels;
	uint8_t* mvpData;
public:
	CTexture(std::string filename);
	CTexture();
	~CTexture();

	inline int getWidth(void) const { return mWidth; }
	inline int getHeight(void) const { return mHeight; }
	inline int getChannels(void) const { return mChannels; }

	ubyte4 getTexel(int x, int y) const;
	ubyte4 getTexel(float x, float y) const;
	void setTexel(int x, int y, const ubyte4& color);

	bool readPNG(std::string filename);
	void writePNG(std::string filename);
};

