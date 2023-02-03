#pragma once

#include "Rect.h"
#include "Colors.h"
#include "Graphics.h"

class Wall
{
public:
	Wall(const Rect& rect, const Color& c);
	Rect getWall() const;
	void draw(Graphics& gfx) const;

private:
	Rect rect;
	Color c;
	int width = 8;

};

