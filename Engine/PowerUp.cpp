#include "PowerUp.h"


PowerUp::PowerUp(Rect& rect, PowerUp::powers in)
	:
	pos( rect.getCenter() ),
	type( in )
{
	switch ( type )
	{
		case PowerUp::powers::bullet:
		{
			col = Colors::MakeRGB( 10 , 10 , 10 );
			break;
		}
		case PowerUp::powers::length:
		{
			col = Colors::Magenta;
			break;
		}
		case PowerUp::powers::balls:
		{
			col = Colors::Green;
			break;
		}
	}
}


void PowerUp::draw(Graphics& gfx) const
{
	if ( !destroyed )
	{
		gfx.DrawRect( Rect::fromCenter( pos , width, height - 2) , Colors::MakeRGB( 200 , 200 , 200 ) );
		gfx.DrawRect( Rect::fromCenter( pos , width - 2, height ) , Colors::MakeRGB( 200 , 200 , 200 ) );

		gfx.DrawRect( Rect::fromCenter( pos , width - 1, height - 3) , col );
		gfx.DrawRect( Rect::fromCenter( pos , width - 3 , height - 1 ) , col );
	}
		
}

void PowerUp::drawBullets( Graphics& gfx )
{
	for ( Bullet& bullet : bullets )
	{
		if ( !bullet.getDestroyed( ) )
		{
			bullet.draw( gfx );
		}
	}
}

void PowerUp::updateBullets( float dt, const Rect& wall )
{
	for ( int i = 0; i < bullets.size(); i++)
	{
		if ( !bullets[ i ].getDestroyed( ) )
		{
			bullets[ i ].update( dt );
			bullets[ i ].wallCollision( wall );
		}
		else
		{
 			bullets.erase( bullets.begin( ) + i );
		}
	}

}

Rect PowerUp::getBullets( )
{
	if ( powerOn )
	{
		for ( Bullet& bullet : bullets )
		{
			return bullet.getRect( );
		}
	}
}

bool PowerUp::shot( Paddle& paddle , const Keyboard& kdb , float dt)
{
	frames += dt;
	if ( powerOn && kdb.KeyIsPressed( VK_SPACE ) && frames >= bulletWait)
	{
		frames = 0.0f;
		bullets.push_back( Bullet( Vec2(paddle.getVec().x + 15.0f, paddle.getVec( ).y ) , Vec2( 0, - 500.0f) ) );
		bullets.push_back( Bullet( Vec2( paddle.getVec( ).x - 15.0f , paddle.getVec( ).y ) , Vec2( 0 , -500.0f ) ) );
		return true;
	}
	return false;
}

Rect PowerUp::getRect() const
{
	return Rect::fromCenter(pos, width / 2.0f, height / 2.0f);
}

void PowerUp::update(float dt)
{
	if (!destroyed)
		pos += vel * dt;

}

bool PowerUp::paddleCollision(Paddle& paddle)
{
	if (!destroyed && getRect().isOverLapping(paddle.getRect()))
	{
		destroyed = true;
		return true;
	}
	return false;

}

bool PowerUp::wallCollision(const Rect& wall)
{
	const Rect rect = getRect();
	if (rect.bottom >= wall.bottom)
	{
		return true;
	}
	return false;
}

void PowerUp::turnOn(  )
{
	powerOn = true;
}

PowerUp::powers PowerUp::getPower( )
{
	return type;
}


PowerUp::Bullet::Bullet( Vec2 pos , Vec2 vel) : pos( pos ), vel( vel )
{
}

void PowerUp::Bullet::draw( Graphics& gfx )
{
	if ( !toBeDestroyed )
	{
		SpriteCodex::DrawBullet( pos , gfx );
	}
	else
	{
		if ( frames <= waitFrames )
			SpriteCodex::DrawBulletDestroyed( pos , gfx );
		else
			destroyed = true;
	}
}

void PowerUp::Bullet::update( float dt )
{
	if ( toBeDestroyed )
	{
		frames += dt;
	}
	else
	{
		pos += vel * dt;
	}
}

void PowerUp::Bullet::wallCollision( const Rect& wall )
{
	const Rect rect = getRect( );
	if ( rect.top <= wall.top )
	{
		toBeDestroyed = true;
	}
}

bool PowerUp::Bullet::brickCollision( Brick& brick )
{
	if ( !toBeDestroyed && getRect( ).isOverLapping( brick.getRect( ) ) && !brick.getDestroyed() )
	{
		brick.collision( );
		toBeDestroyed = true;
		return true;
	}
	return false;
}

Rect PowerUp::Bullet::getRect( ) const
{
	return Rect::fromCenter( pos , width / 2.0f , height / 2.0f );
}

bool PowerUp::Bullet::getDestroyed( ) const
{
	return destroyed;
}

