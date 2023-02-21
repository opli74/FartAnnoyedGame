#include "PowerUp.h"


PowerUp::PowerUp(Rect& rect)
	:
	pos(rect.getCenter())
{
	type = bulletTypes::bulletV1;
}

void PowerUp::draw(Graphics& gfx) const
{
	if ( !destroyed )
	{
		gfx.DrawRect( Rect::fromCenter( pos , width + 1 , height + 1 ) , Colors::MakeRGB( 200 , 200 , 200 ) );
		gfx.DrawRect( Rect::fromCenter( pos , width , height ) , Colors::MakeRGB( 10 , 10 , 10 ) );
	}
		
}

void PowerUp::drawBullets( Graphics& gfx ) const
{
	for ( const Bullet& bullet : bullets )
	{
		if ( !bullet.getDestroyed( ) )
		{
			bullet.draw( gfx );
		}
	}
}

void PowerUp::updateBullets( float dt, const Rect& wall )
{
	for ( Bullet& bullet : bullets )
	{
		if ( !bullet.getDestroyed( ) )
		{
			bullet.update( dt );
			bullet.wallCollision( wall );
		}
	}
}

Rect PowerUp::getBullets( )
{
	if ( shoot )
	{
		for ( Bullet& bullet : bullets )
		{
			return bullet.getRect( );
		}
	}
}

void PowerUp::shot( Paddle& paddle , const Keyboard& kdb , float dt)
{
	frames += dt;
	if ( shoot && kdb.KeyIsPressed( VK_SPACE ) && frames >= bulletWait)
	{
		frames = 0.0f;
		bullets.push_back( Bullet( paddle.getVec() ) );
	}
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

void PowerUp::wallCollision(const Rect& wall)
{
	const Rect rect = getRect();
	if (rect.bottom >= wall.bottom)
	{
		destroyed = true;
	}

}

void PowerUp::givePower(  )
{
	shoot = true;
}

bool PowerUp::getPower( )
{
	return shoot;
}

PowerUp::bulletTypes PowerUp::getType( ) const
{
	return type;
}

void PowerUp::setType( bulletTypes in )
{
	type = in;
}

PowerUp::Bullet::Bullet( Vec2 pos ) : pos( pos )
{
}

void PowerUp::Bullet::draw( Graphics& gfx ) const
{
	if( !destroyed )
		gfx.DrawRect( Rect::fromCenter( pos , width , height ) , Colors::Cyan );
}

void PowerUp::Bullet::update( float dt )
{
	pos += vel * dt;
}

void PowerUp::Bullet::wallCollision( const Rect& wall )
{
	const Rect rect = getRect( );
	if ( rect.top <= wall.top )
	{
		destroyed = true;
	}
}

bool PowerUp::Bullet::brickCollision( Brick& brick )
{
	if ( !destroyed && getRect( ).isOverLapping( brick.getRect( ) ) && !brick.getDestroyed() )
	{
		brick.collision( );
		destroyed = true;
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

