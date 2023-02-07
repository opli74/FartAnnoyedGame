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
	bool isCollidingBall(const Ball& ball) const;
	void executeBallCollision(Ball& ball, const bool& type);
	Rect getRect() const;


private:
	static constexpr float padding = 1.0f;
	Rect rect;
	Color c, l, d;
	bool destroyed = false;
	float width = 1.0f;
};

