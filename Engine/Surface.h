#pragma once

#include "Colors.h"
#include <string>
#include "RectI.h"

class Surface
{
public:
	Surface(const std::string& filename,const bool& IN_inverseY);
	Surface(int width, int height);
	Surface(const Surface&);
	~Surface();
	Surface& operator=(const Surface&);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const; 
	RectI GetRect() const
	{
		return { 0,width,0,height };
	}
private:
	
	Color* pPixels = nullptr;
	int width;
	int height;
	bool inverseY = true;
};