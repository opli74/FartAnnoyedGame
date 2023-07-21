#include "Brick.h"


Brick::Brick( const Rect& rect , int x_ , int y_ , Color c_ , const int health , Type type )
	:
	rect( rect ) ,
	health( health ) ,
	type( type ),
	x( x_ ) ,
	y( y_ )
{
	if ( health == 0 )
		destroyed = true;
	c = c_;

	d.SetR( unsigned char( float( c.GetR( ) ) * 0.85f ) );
	d.SetG( unsigned char( float( c.GetG( ) ) * 0.85f ) );
	d.SetB( unsigned char( float( c.GetB( ) ) * 0.85f ) );

	l.SetR( c.GetR( ) + unsigned char( ( float( 255u - c.GetR( ) ) * 0.4f ) ) );
	l.SetG( c.GetG( ) + unsigned char( ( float( 255u - c.GetG( ) ) * 0.4f ) ) );
	l.SetB( c.GetB( ) + unsigned char( ( float( 255u - c.GetB( ) ) * 0.4f ) ) );
}
	
void Brick::draw(Graphics& gfx) const
{
	if ( !destroyed )
	{

		if ( type != Type::empty )
		{
			
			gfx.DrawRect( rect.getExpanded( -padding ) , c );

			if ( type == Type::extra || type == Type::invinc )
			{
				gfx.DrawRect( Rect( rect.left + padding , rect.right - padding , rect.top + padding , ( rect.top + padding ) + width + 1 ) , l );
				gfx.DrawRect( Rect( rect.left + padding , ( rect.left + padding ) + width + 1 , rect.top + padding , rect.bottom - padding ) , l );
				gfx.DrawRect( Rect( rect.left + padding , rect.right - padding , ( rect.bottom - padding ) - width - 1 , ( rect.bottom - padding ) ) , d );
				gfx.DrawRect( Rect( ( rect.right - padding ) - width - 1 , ( rect.right - padding ) , rect.top + padding , rect.bottom - padding ) , d );
			}

			if ( hover )
			{
				gfx.DrawRect( rect , Colors::MakeRGB( 250 , 250 , 250 ) , 2 );
			}
		}
		else
		{
			gfx.DrawRect( rect.getExpanded( -padding ) , c , 1 );
		}

		if ( hit )
		{
			switch ( times )
			{
				case 1:
				{
					gfx.DrawRect( Rect( rect.left + padding + 25 , rect.right - padding , ( rect.bottom - padding ) - width - 1 , ( rect.bottom - padding ) ) , Colors::MakeRGB( 225 , 225, 225 ) );
					gfx.DrawRect( Rect( ( rect.right - padding ) - width - 1 , ( rect.right - padding ) , rect.top + padding + 5, rect.bottom - padding ) , Colors::MakeRGB( 225 , 225 , 225 ) );
					break;
				}
				case 2:
				{
					gfx.DrawRect( Rect( rect.left + padding + 10, rect.right - padding , ( rect.bottom - padding ) - width - 1 , ( rect.bottom - padding ) ) , Colors::MakeRGB( 225 , 225 , 225 ) );
					gfx.DrawRect( Rect( ( rect.right - padding ) - width - 1 , ( rect.right - padding ) , rect.top + padding, rect.bottom - padding ) , Colors::MakeRGB( 225 , 225 , 225 ) );
					break;
				}
				case 3:
				{
					gfx.DrawRect( rect.getExpanded( -padding ) , Colors::MakeRGB( 225 , 225 , 225 ) );
					break;
				}
				case 4:
				{
					gfx.DrawRect( Rect( rect.left + padding , rect.right - padding - 10 , rect.top + padding , ( rect.top + padding ) + width + 1 ) , Colors::MakeRGB( 225 , 225 , 225 ) );
					gfx.DrawRect( Rect( rect.left + padding , ( rect.left + padding ) + width + 1 , rect.top + padding , rect.bottom - padding ) , Colors::MakeRGB( 225 , 225 , 225 ) );
					break;
				}
			}
				
		}


	}
}

bool Brick::isCollidingBall(const Ball& ball)
{
	if ( type == Type::invinc )
	{
		destroyed = false;
		health = 999;
	}
	else if ( health > 0 )
	{
		destroyed = false;
	}
	else
	{
		destroyed = true;
	}

	return ( !destroyed && rect.isOverLapping( ball.getRect( ) ) );
}


void Brick::executeBallCollision(Ball& ball)
{
	Vec2 ballPrevPos = ball.prevPosition();
	Vec2 ballPos = Vec2(0, 0);

	float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballPrevPos.y - rect.getCenter().y);
	float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballPrevPos.x - rect.getCenter().x);

	if (wy > hx)
	{
		if (wy > -hx)
		{
			//bottom
			ballPos.y += rect.bottom - ball.getRect().top;
			ball.reboundY(true);
			health--;
		}
		else
		{
			//left
			ballPos.x -= ball.getRect().right - rect.left;
			ball.reboundX(false);
			health--;
		}
	}
	else
	{
		if (wy > -hx)
		{
			//right
			ballPos.x += rect.right - ball.getRect().left;
			ball.reboundX(true);
			health--;
		}
		else
		{
			//top
			ballPos.y -= ball.getRect().bottom - rect.top;
			ball.reboundY(false);
			health--;
		}
	}

	ballPrevPos += ballPos;
	ball.setPosition(ballPrevPos);
}

void Brick::collision( )
{
	health--;
}

Color Brick::getColor() const
{
	return c;
}

Brick::Type Brick::getType( ) const
{
	return type;
}

void Brick::setColor(const Color& in)
{
	c = in;
}

Rect Brick::getRect() const
{
	return rect;
}

bool Brick::getDestroyed() 
{
	if ( type == Type::invinc )
	{
		destroyed = false;
		health = 999;
	}
	else if ( health > 0 )
	{
		destroyed = false;
	}
	else
	{
		destroyed = true;
	}
	return destroyed;
}

void Brick::color( float dt )
{
	if ( hit )
	{
		frames += dt;
		if ( frames > 0.065f )
		{

			frames = 0.0f;
			times++;

			if ( times >= 5 )
			{
				hit = false;
				times = 0;
			}
		}

	}
}

int Brick::getX( )
{
	return x;
}

int Brick::getY( )
{
	return y;
}

bool Brick::isHover( Vec2 pos )
{

	if ( type == Type::empty )
	{
		if ( getRect( ).isOverLapping( pos ) )
		{
			setColor( Colors::MakeRGB( 180 , 180 , 180 ) );
			return true;
		}

		setColor( Colors::MakeRGB( 60 , 60 , 60 ) );
		return false;
	}
	else
	{
		if ( getRect( ).isOverLapping( pos ) )
		{
			hover = true;
			return true;
		}
		else
		{
			hover = false;
			return false;
		}
	}
	return false;

}
