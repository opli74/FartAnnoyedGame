#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Rect.h"

class Ball
{
public:
	Ball(const Vec2& pos, const Vec2& vel);
	void draw(Graphics& gfx) const;
	void update(float dt);
	bool wallCollision(const Rect& wall);
	void reboundX();
	void reboundY();
	Rect getRect() const;
private:
	
	static constexpr float radius = 7.0f;
	Vec2 vel;
	Vec2 pos;
};

