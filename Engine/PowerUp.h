#pragma once
#include <vector>
#include "GetRandom.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Brick.h"

class PowerUp
{
public:


	enum class bulletTypes
	{
		bulletV1,
		bulletV2,
		bulletV3
	};


	class Bullet
	{
	public:
		Bullet(Vec2 pos);
		void draw( Graphics& gfx) const;
		void update( float dt );
		void wallCollision( const Rect& wall );
		bool brickCollision( Brick& brick );
		Rect getRect( ) const;
		bool getDestroyed( ) const;

	private:
		Vec2 pos;
		const float width = 2.5f;
		const float height = 4.0f;
		const Vec2 vel = Vec2( 0.0f , -250.0f );
		bool destroyed = false;
	};

	PowerUp() = default;
	PowerUp(Rect& rect);
	void draw(Graphics& gfx) const;
	void drawBullets( Graphics& gfx ) const;
	void updateBullets( float dt , const Rect& wall );
	Rect getBullets( );
	void update(float dt);
	bool paddleCollision(Paddle& paddle);
	void wallCollision(const Rect& wall);
	void givePower( );
	bool getPower( );
	bulletTypes getType( ) const;
	void setType( bulletTypes in );
	void shot( Paddle& paddle , const Keyboard& kdb, float dt );
	Rect getRect() const;

public:
	std::vector<Bullet> bullets;

private:
	float frames = 1.0f;    
	float bulletWait = 0.5f;
	const float width = 15.0f;
	const float height = 5.0f;
	Vec2 pos;
	const Vec2 vel = Vec2(0.0f, 150.0f);
	bool destroyed = false;
	bool shoot = false;

	bulletTypes type;

};

