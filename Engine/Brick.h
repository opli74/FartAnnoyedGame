#pragma once

#include "Rect.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"


class Brick
{
public: 
	Brick() = default;
	Brick(const Rect& rect, Color c);
	void draw(Graphics& gfx) const;
	bool isCollidingBall(Ball& ball);
	void executeBallCollision(Ball& ball);

private:
	static constexpr float padding = 1.0f;
	Rect rect;
	Color c;
	bool destroyed = false;
};

