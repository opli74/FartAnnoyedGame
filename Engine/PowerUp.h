#pragma once
#include <vector>
#include "GetRandom.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Brick.h"
#include "SpriteCodex.h"
#include "Colors.h"

class PowerUp
{
public:
	enum class powers
	{
		bullet,
		length,
		balls,
		block, 
		bomb
	};

	class Bullet
	{
	public:
		Bullet( ) = default;
		Bullet(Vec2 pos, Vec2 vel);
		void draw( Graphics& gfx);
		void update( float dt );
		void wallCollision( const Rect& wall );
		bool brickCollision( Brick& brick );
		Rect getRect( ) const;
		bool getDestroyed( ) const;

	private:
		Vec2 pos;
		float width = 4.0f;
		float height = 8.0f;
		Vec2 vel;
		bool toBeDestroyed = false;
		bool destroyed = false;
		float frames = 0.0f;
		float waitFrames = 0.15f;
	};

	PowerUp() = default;
	PowerUp(Rect& rect, PowerUp::powers in);
	void draw(Graphics& gfx) const;
	void drawBullets( Graphics& gfx );
	void updateBullets( float dt , const Rect& wall );
	bool bulletExists( );
	Rect getBullets( );
	void update(float dt);
	bool paddleCollision(Paddle& paddle);
	bool wallCollision(const Rect& wall);
	void turnOn( );
	PowerUp::powers getPower( );
	bool shot( Paddle& paddle , const Keyboard& kdb, float dt , bool shoot);
	Rect getRect() const;

public:
	std::vector<Bullet> bullets;

private:
	Color col;
	std::vector<int> removeBullets;
	float frames = 1.0f;    
	float bulletWait = 0.35f;
	float width = 15.0f;
	float height = 5.0f;
	Vec2 pos;
	Vec2 vel = Vec2(0.0f, 150.0f);
	bool destroyed = false;
	bool powerOn = false;

	powers type;


};

