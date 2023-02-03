#pragma once

#include "Vec2.h"

class Rect
{
public:
	Rect() = default;
	Rect(float left, float right, float top, float bottom);
	Rect(const Vec2& topLeft, const Vec2& bottomRight);
	Rect(const Vec2& topLeft, float width, float height);
	bool isOverLapping(const Rect& rect) const;
	static Rect fromCenter(const Vec2& center, float halfWidth, float halfHeight);
	Rect getExpanded(float offset) const;


public:
	float left, right, top, bottom;
};

