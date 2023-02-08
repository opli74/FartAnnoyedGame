#pragma once

#include "Rect.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"


class Brick
{
public: 
	Brick() = default;
	Brick(const Rect& rect, Color c, const int health);
	void draw(Graphics& gfx) const;
	bool isCollidingBall(const Ball& ball);
	void executeBallCollision(Ball& ball, const bool& type);
	Color getColor() const;
	void setColor(const Color& in);
	Rect getRect() const;
	bool getDestroyed() const;
	void color();

public:
	bool hit = false;

private:
	
	int frames = 0;
	static constexpr float padding = 1.0f;
	Rect rect;
	Color c = Colors::MakeRGB(255, 137, 0) , l = Colors::MakeRGB(230, 230, 230) , d = Colors::MakeRGB(130, 130, 130);;
	bool destroyed = false;
	float width = 1.0f;
	int health;
};

