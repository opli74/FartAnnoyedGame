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
	void drawBorder(Graphics& gfx) const;
	void drawBackground(Graphics& gfx) const;


private:
	Rect rect;
	Color c;
	Color cBevel;
	Color greyOne = Colors::MakeRGB(30, 30, 30);
	Color greyTwo = Colors::MakeRGB(36, 36, 36);
	int width = 18;

	int cellX = 14;
	int cellY = 14;

	int w;
	int h;

	float cellW;
	float cellH;

	Vec2 topLeft;

};

