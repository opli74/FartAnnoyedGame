#pragma once

#include "Rect.h"
#include "Graphics.h"
#include "Colors.h"

class Brick
{
public: 
	Brick(const Rect& rect, Color c);
	void draw(Graphics& gfx) const;

private:
	Rect rect;
	Color c;
	bool destroyed = false;
};

