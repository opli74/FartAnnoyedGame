#pragma once

#include "Graphics.h"
#include "Ball.h"	
#include "Vec2.h"
#include "Keyboard.h"
#include "SpriteCodex.h"

class Paddle
{
public:
	Paddle(const Vec2& pos, float halfWidth, float halfHeight);
	void draw(Graphics& gfx) const;
	bool ballCollision(Ball& ball);
	void wallCollision(const Rect& wall);
	void update(const Keyboard& kdb, float dt);
	Rect getRect() const;
	Vec2 getVec() const;
	void setPos(const Vec2& pos);

private:
	Color c = Colors::White;
	Vec2 pos;
	float halfWidth;
	float halfHeight;
	const float speed = BALL_SPEED;
	bool test = false;
};

