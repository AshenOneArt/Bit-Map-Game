#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface(const std::string& filename,const bool& IN_inverseY)
{
	std::ifstream file(filename, std::ios::binary);
	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));
	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));
	assert(bmInfoHeader.biBitCount == 24);
	assert(bmInfoHeader.biCompression == BI_RGB);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	pPixels = new Color[width * height];	
	file.seekg(bmFileHeader.bfOffBits);
	
	inverseY = IN_inverseY;
	int heightStart, heightEnd, heightIterator;
	if (!inverseY)
	{
		heightStart = 0;
		heightEnd = height;
		heightIterator = 1;
	}
	else
	{
		heightStart = height-1;
		heightEnd = 0;
		heightIterator = -1;
	}
	for (int Sy = heightStart; Sy != heightEnd; Sy += heightIterator)
	{
		for (int Sx = 0; Sx < width; Sx++)
		{
			PutPixel(Sx, Sy, Color(file.get(), file.get(), file.get()));
		}		
	} 
	
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width * height])	
{
}

Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height)
{
	inverseY = rhs.inverseY;
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface& Surface::operator=(const Surface& rhs)
{
	width = rhs.width;
	height = rhs.height;
	inverseY = rhs.inverseY;

	delete[] pPixels;
	pPixels = new Color[width * height];

	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
