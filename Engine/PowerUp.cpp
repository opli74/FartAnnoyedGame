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
		gfx.DrawRect( Rect::fromCenter( pos , width, height - 2) , Colors::MakeRGB( 200 , 200 , 200 ) );
		gfx.DrawRect( Rect::fromCenter( pos , width - 2, height ) , Colors::MakeRGB( 200 , 200 , 200 ) );

		gfx.DrawRect( Rect::fromCenter( pos , width - 1, height - 3) , Colors::MakeRGB( 10 , 10 , 10 ) );
		gfx.DrawRect( Rect::fromCenter( pos , width - 3 , height - 1 ) , Colors::MakeRGB( 10 , 10 , 10 ) );
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
	if ( shoot )
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
	if ( shoot && kdb.KeyIsPressed( VK_SPACE ) && frames >= bulletWait)
	{
		frames = 0.0f;
		bullets.push_back( Bullet( paddle.getVec() , Vec2( 0, - 500.0f) ) );
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

