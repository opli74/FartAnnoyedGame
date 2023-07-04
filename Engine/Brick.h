#pragma once

#include "Rect.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick
{


public: 
	enum class Type
	{
		normal ,
		extra ,
		invinc , 
		empty
	};

	Brick() = default;
	Brick(const Rect& rect, Color c_, const int health, Type type);
	void draw(Graphics& gfx) const;
	bool isCollidingBall(const Ball& ball);
	void executeBallCollision(Ball& ball);
	void collision( );
	Color getColor() const;
	Type getType( ) const;
	void setColor(const Color& in);
	Rect getRect() const;
	bool getDestroyed(); 
	void color(float dt);

public:
	bool hit = false;
	int health;

private:

	float frames = 0.0f;
	static constexpr float padding = 1.0f;
	Rect rect;
	Color c = Color( NULL , NULL , NULL ) , l = Color( NULL , NULL , NULL ) , d = Color( NULL , NULL , NULL );
	bool destroyed = false;
	float width = 1.0f;
	int times = 0;
	Type type;
};

