#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Rect
{
public:
	Rect() = default;
	Rect(float left, float right, float top, float bottom);
	Rect(const Vec2& topLeft, const Vec2& bottomRight);
	Rect(const Vec2& topLeft, float width, float height);
	bool isOverLapping(const Rect& rect) const;

private:
	float left, right, top, bottom;
};

