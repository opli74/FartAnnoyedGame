#pragma once
#include "GetRandom.h"
#include "Graphics.h"
#include "Paddle.h"
class PowerUp
{
public:
	PowerUp() = default;
	PowerUp(Rect& rect);
	void draw(Graphics& gfx) const;
	void update(float dt);
	bool paddleCollision(Paddle& paddle);
	void wallCollision(const Rect& wall);

	Rect getRect() const;

private:
	const float width = 20.0f;
	const float height = 8.0f;
	Vec2 pos;
	const Vec2 vel = Vec2(0.0f, 150.0f);
	bool destroyed = false;

};

