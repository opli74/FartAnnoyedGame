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
	Brick( const Rect& rect , int x_, int y_,  Color c_ , const int health , Type type );
	
	//setters
	void draw( Graphics& gfx ) const;

	void color( float dt );

	void setColor( const Color& in );

	void executeBallCollision( Ball& ball );
	void collision( );

	//getters
	bool isHover( Vec2 pos );
	
	int getX( );
	int getY( );

	bool getDestroyed( );

	Rect getRect( ) const;
	Color getColor( ) const;
	Type getType( ) const;

	bool isCollidingBall( const Ball& ball );

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

	bool hover = false;

	int x = 0 , y = 0;
};

