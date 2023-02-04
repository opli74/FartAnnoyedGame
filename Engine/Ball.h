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
	void reboundX(const bool& dir);
	void reboundY(const bool& dir);
	Vec2 prevPosition() const;
	Vec2 getPosition() const;
	Vec2 getVelocity() const;
	Rect getRect() const;
	void setDirection(const Vec2& vel_);
	void SetPosition(const Vec2& pos_);

public:
	Vec2 pos;
	

private:
	static constexpr float radius = 7.0f;
	Vec2 vel;
	Vec2 prevPos;
	float speed = 300.0f;


};

