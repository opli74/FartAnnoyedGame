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
	void drawLines(Graphics& gfx) const;
	void drawBackground(Graphics& gfx) const;


private:
	Rect rect;
	Color c;
	Color borderL = Colors::MakeRGB(165, 165, 165);
	Color borderD = Colors::MakeRGB(75, 75, 75);
	Color l = Colors::MakeRGB(65, 65, 65);
	Color d = Colors::MakeRGB(45, 45, 45);
	Color greyOne = Colors::MakeRGB(30, 30, 30);
	Color greyTwo = Colors::MakeRGB(36, 36, 36);
	float width = 18.0f;

	int cellX = 18;
	int cellY = 18;

	float w;
	float h;

	float cellW;
	float cellH;

	Vec2 topLeft;

};

