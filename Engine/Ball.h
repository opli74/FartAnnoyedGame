#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Rect.h"



class Ball
{
public:
	Ball( ) = default;
	Ball(const Vec2& pos, Vec2& vel);
	void draw(Graphics& gfx) const;
	void update(float dt);
	bool wallCollision(const Rect& wall, bool restart_ );
	void reboundX();
	void reboundY();
	void reboundX(const bool& dir);
	void reboundY(const bool& dir);
	Vec2 prevPosition() const;
	Vec2 getPosition() const;
	Vec2 getVelocity() const;
	bool getRestart() const;
	void setDirection(Vec2& vel_);
	void setPosition(const Vec2& pos_);
	void switchRestart();
	Rect getRect() const;


private:
	bool restart = false;
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	Vec2 prevPos;
};

