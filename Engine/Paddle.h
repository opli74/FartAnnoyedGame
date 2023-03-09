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
	void draw(Graphics& gfx);
	bool ballCollision(Ball& ball);
	void wallCollision(const Rect& wall);
	void update(const Keyboard& kdb, float dt, float time);
	void lengthPwrUp();
	void lengthPwrUpReset( );
	Rect getRect() const;
	Vec2 getVec() const;
	void setPos(const Vec2& pos);
	void setSpeed( );

private:
	Color c = Colors::White;
	Vec2 pos;
	float halfWidth;
	float longHalfWidth = halfWidth + 5.0f;
	float maxLength = 73.0f;
	float diff;
	float halfHeight;
	float speed = G_BALL_SPEED + 50.0f;
	bool test = false;
	bool incLength = false;
	int amount = 0;
	float frames = 0.0f;
};

