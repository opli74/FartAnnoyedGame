#include "Paddle.h"
#define _USE_MATH_DEFINES
#include <Math.h>


Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	:
	pos(pos),
	halfWidth(halfWidth),
	halfHeight(halfHeight)
{
	diff = ( ( longHalfWidth - halfWidth ) / 2 ) * 2;
}

void Paddle::draw(Graphics& gfx)
{
	if ( !incLength )
	{
		SpriteCodex::DrawPaddle( pos , gfx , 0 );
	}
	else
	{
		if ( amount <= int(diff) && 
			 frames >= 0.03f		)
		{
			amount++;
			frames = 0;
		}
		SpriteCodex::DrawPaddle( pos , gfx , amount );
	}
}

bool Paddle::ballCollision(Ball& ball)
{


	if (getRect().isOverLapping(ball.getRect()))
	{
		Rect paddleRect = getRect();
		Rect ballRect = ball.getRect();
		Vec2 ballCurrPos = ball.getPosition();
		Vec2 ballPosAdjustment = { 0.0f, 0.0f };

		float wy = ((ballRect.right - ballRect.left) + (paddleRect.right - paddleRect.left)) * (ballCurrPos.y - pos.y);
		float hx = ((ballRect.bottom - ballRect.top) + (paddleRect.bottom - paddleRect.top)) * (ballCurrPos.x - pos.x);

		if (wy > hx)
		{
			if (wy < -hx)
			{
				// Left side collision
				ballPosAdjustment.x -= ballRect.right - paddleRect.left;
				ball.reboundX(false);
				ballPosAdjustment.y += (ball.getVelocity().y > 0.0f) ? (paddleRect.bottom - ballRect.top) : -(ballRect.bottom - paddleRect.top);
			}
			else
			{
				// Top side collision
				ballPosAdjustment.y -= ballRect.top - paddleRect.bottom;
				ball.reboundY(true);
			}
		}
		else
		{
			if (wy > -hx)
			{
				// Right side collision
				ballPosAdjustment.x += paddleRect.right - ballRect.left;
				ball.reboundX(true);
				ballPosAdjustment.y += (ball.getVelocity().y > 0.0f) ? (paddleRect.bottom - ballRect.top) : -(ballRect.bottom - paddleRect.top);
			}
			else
			{
				// Bottom side collision (45 degrees bounce)
				ballPosAdjustment.y -= ballRect.bottom - paddleRect.top;

				// Calculate relative X position on the paddle
				float relativeX = incLength ? ((ballCurrPos.x - pos.x) / longHalfWidth) : ((ballCurrPos.x - pos.x) / halfWidth);

				// Calculate bounce angle based on relative X position
				float bounceAngle = relativeX * 0.7853982; // 45 degrees in radians

				// Set ball direction based on bounce angle
				ball.setDirection(Vec2(sinf(bounceAngle), -cosf(bounceAngle)).Normalize() * G_BALL_SPEED);
				return true; // Collision handled, exit early
			}
		}

		ballCurrPos += ballPosAdjustment;
		ball.setPosition(ballCurrPos);
	}

	return false; // No collision

	//if (getRect().isOverLapping(ball.getRect()))
	//{
	//	Rect rect = getRect();
	//	Vec2 ballCurrPos = ball.getPosition();
	//	Vec2 ballPos = Vec2(0, 0);

	//	float wy = ((ball.getRect().right - ball.getRect().left) + (rect.right - rect.left)) * (ballCurrPos.y - pos.y);
	//	float hx = ((ball.getRect().bottom - ball.getRect().top) + (rect.bottom - rect.top)) * (ballCurrPos.x - pos.x);

	//	if (wy > hx)
	//	{
	//		if (wy < -hx)
	//		{
	//			//left
	//			ballPos.x -= ball.getRect().right - rect.left;
	//			ball.reboundX(false);
	//			if (ball.getVelocity().y > 0.0f)
	//				ballPos.y += rect.bottom - ball.getRect().top;
	//			else
	//				ballPos.y -= ball.getRect().bottom - rect.top;
	//		}
	//		else
	//		{
	//			ballPos.y -= ball.getRect( ).top - rect.bottom;
	//			ball.reboundY( true );
	//		}
	//	}
	//	else
	//	{
	//		if (wy > -hx)
	//		{
	//			//right
	//			ballPos.x += rect.right - ball.getRect().left;
	//			ball.reboundX(true);
	//			if (ball.getVelocity().y > 0.0f)
	//				ballPos.y += rect.bottom - ball.getRect().top;
	//			else
	//				ballPos.y -= ball.getRect().bottom - rect.top;
	//		}
	//		else
	//		{
	//			//top
	//			ballPos.y -= ball.getRect().bottom - rect.top;
	//			float relativeX = 0.0f;
	//			if ( incLength )
	//				relativeX = ( ballCurrPos.x - pos.x ) / ( longHalfWidth );
	//			else
	//				relativeX = ( ballCurrPos.x - pos.x ) / ( halfWidth );

	//			//45 degrees
	//			float bounceAngle = relativeX * 0.7853982;

	//			ball.setDirection(Vec2(sinf(bounceAngle), -cosf(bounceAngle)).Normalize() * G_BALL_SPEED);
	//			test = true;
	//		}
	//	}
	//	ballCurrPos += ballPos;
	//	ball.setPosition(ballCurrPos);
	//	
	//}
	//return false;
}

void Paddle::wallCollision(const Rect& wall)
{
	const Rect rect = getRect();
	if (rect.left <= wall.left)
	{
		pos.x += wall.left - rect.left ;
	}
	if (rect.right >= wall.right)
	{
		pos.x -= rect.right - wall.right;
	}
}

void Paddle::update(const Keyboard& kbd, float dt, float time)
{
	if ( incLength )
	{
		frames += dt;
		diff = ( ( longHalfWidth - halfWidth ) / 2 ) * 2;
	}
	else
	{
		frames = 0;
		amount = 0;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

void Paddle::lengthPwrUp()
{
	if ( longHalfWidth < maxLength )
		longHalfWidth += 3.0f;
	incLength = true;
}

void Paddle::lengthPwrUpReset( )
{
	incLength = false;
	longHalfWidth = halfWidth + 5.0f;
}

Rect Paddle::getRect() const
{
	if ( incLength )
		return Rect::fromCenter(pos, longHalfWidth, halfHeight);

	return Rect::fromCenter( pos , halfWidth , halfHeight );
}

Vec2 Paddle::getVec() const
{
	return pos;
}

void Paddle::setPos(const Vec2& pos_)
{
	pos = pos_;
}

void Paddle::setSpeed( )
{
	speed = G_BALL_SPEED + 55.0f;
}

