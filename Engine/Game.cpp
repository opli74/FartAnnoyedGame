/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

namespace Random
{
	std::mt19937 mt{ std::random_device{}() };

	int getRand( int min, int max )
	{
		std::uniform_int_distribution<int> die(min, max);
		return die(mt);
	}
	float getRand( float min , float max )
	{
		std::uniform_real_distribution<float> die( min , max );
		return die( mt );
	}
}

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	wall(Rect(110.0f, 690.0f, 0.0f, 600.0f), Colors::MakeRGB(150,150,150)),
	paddle( Vec2( 400.0f , 500.0f ) , PADDLE_HALF_WIDTH , 8 )
	
{
	offset = getOffset( );
	balls[ 0 ] = Ball( Vec2( 400.0f + offset , ( 500.0f - 0.0f ) ) , Vec2( BALL_SPEED , BALL_SPEED ) );

	soundPlay = Sound( L"Sounds\\arkstart.wav" );
	soundPlay.StopAll( );
	soundPlay.Play( 1.0f , 0.2f );

	resetMy( );

}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.01f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	start = gfx.timer(dt, start, 1.25f);

	if (wnd.kbd.KeyIsPressed('1'))
	{
		if (!pressed)
		{
			offset = getOffset( );
			balls[ 0 ].setPosition( Vec2( 400.0f + offset , 500.0f - 15.0f ) );
			paddle.setPos(Vec2(400.0f, 500.0f));
			paddle.lengthPwrUpReset( );

			if (current2dIndex > 0)
				current2dIndex -= 1;

			resetMy();

			pressed = true;

			soundPlay = Sound( L"Sounds\\arkstart.wav" );
			soundPlay.StopAll( );
			soundPlay.Play( 1.0f, 0.25f );
		}

	}
	else if (wnd.kbd.KeyIsPressed('2') || destroyed == (nBricks - nonBrickAmount) - indestructable)
	{

		if (!pressed)
		{
			offset = getOffset( );
			balls[ 0 ].setPosition( Vec2( 400.0f + offset , 500.0f - 15.0f ) );
			paddle.setPos(Vec2(400.0f, 500.0f));
			paddle.lengthPwrUpReset( );

			start = false;
			spaceClicked = false;

			if (current2dIndex < 3)
				current2dIndex += 1;

			resetMy();

			pressed = true;

			soundPlay = Sound( L"Sounds\\arkstart.wav" );
			soundPlay.StopAll( );
			soundPlay.Play( 1.0f , 0.25f );
		}

	}
	else
	{
		pressed = false;
	}


	if (start)
	{
		if ( !spaceClicked )
		{
			for ( int i = 0; i < currBalls ; i++ )
			{
				balls[ i ].setPosition( Vec2( paddle.getVec( ).x + offset , 500.0f - 15.0f ) );
			}
		}
		if ( wnd.kbd.KeyIsPressed( VK_UP ) && !spaceClicked )
		{
			spaceClicked = true;
			soundPlay = Sound( L"Sounds\\arkpad.wav" );
			soundPlay.StopAll( );
			soundPlay.Play( 1.0f , 0.25f );
		}

		if ( spaceClicked )
		{
			for ( int i = 0 ; i < currBalls ; i++ )
			{ 
				balls[ i ].update( dt );
				if ( currBalls > 1 )
				{
					if ( balls[ i ].wallCollision( wall.getWall( ) , false ) )
					{
						for ( int f = i; f < currBalls; f++ )
						{
							balls[ f ] = balls[ f + 1 ];
						}
						currBalls--;
					}
				}
				else
				{
					balls[ i ].wallCollision( wall.getWall( ) , true );
					hasBalls = false;
				}
			}
		}

		paddle.update(wnd.kbd, dt);
		
		if (balls[ 0 ].getRestart( ) )
		{
			offset = getOffset( );
			balls[ 0 ].switchRestart( );
			balls[ 0 ].setPosition( Vec2( 400.0f + offset , 500.0f - 15.0f ) );
			balls[ 0 ].setDirection( Vec2( 0.0f , 5.0f ) );
			paddle.setPos(Vec2(400.0f, 500.0f));
			start = false;
			spaceClicked = false;
			soundPlay = Sound( L"Sounds\\arkrestart.wav" );
			soundPlay.StopAll( );
			soundPlay.Play( 1.0f , 0.25f );

		}

		bool collisionHappened = false;
		float collisionDisSq;
		int collisionIndex = 0;
		int ballIndex = 0;

		for ( int i = 0; i < nBricks; i++ )
		{
			bricks[ i ].color( dt );
			for (  int b = 0; b < currBalls ; b++ )
			{
				if ( bricks[ i ].isCollidingBall( balls[ b ] ) )
				{
					if ( brickArray[ current2dIndex ][ 1 ][ i ] != 0 )
					{
						const float newCollisionDistSq = ( balls[ b ].getPosition( ) - bricks[ i ].getRect( ).getCenter( ) ).GetLengthSq( );
						if ( collisionHappened )
						{
							if ( newCollisionDistSq < collisionDisSq )
							{
								collisionDisSq = newCollisionDistSq;
								collisionIndex = i;
								ballIndex = b;
							}
						}
						else
						{
							collisionDisSq = newCollisionDistSq;
							collisionIndex = i;
							collisionHappened = true;
							ballIndex = b;
						}
					}
				}
			}
			for ( PowerUp& power : powers )
			{
				for ( int f = 0; f < power.bullets.size( ); f++ )
				{
					if ( power.bullets[ f ].brickCollision( bricks[ i ] ) )
					{
						bricks[ i ].hit = true;
						if ( bricks[ i ].getDestroyed( ) )
							destroyed++;
					}

				}
			}
		}

		
		if (collisionHappened)
		{
			
			if (brickArray[current2dIndex][1][collisionIndex] == 6 || brickArray[ current2dIndex ][ 1 ][ collisionIndex ] == 7 )
			{
				soundPlay = Sound( L"Sounds\\arkstrongbrick.wav" );
			}
			else
			{
				soundPlay = Sound( L"Sounds\\arkbrick.wav" );
			}

			soundPlay.StopAll( );
			soundPlay.Play( 1.0f , 0.25f );
			
			bricks[ collisionIndex ].executeBallCollision( balls[ ballIndex ] );
			
			if (bricks[collisionIndex].getDestroyed())
			{

				if ( Random::getRand( 0 , 5 ) == 5)
				{
					switch ( Random::getRand( 0 , 2 ) )
					{
						case 0:
						{
							powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::bullet ) );
							break;
						}
						case 1:
						{
							powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::length ) );
							break;
						}
						case 2:
						{
							powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::balls ) );
							break;
						}
					}
				}
				destroyed++;
			}
				
			bricks[collisionIndex].hit = true;
		}

		for ( int i = 0 ; i < currBalls; i++ )
		{
			if ( paddle.ballCollision( balls[ i ] ) && !wnd.kbd.KeyIsPressed( VK_SPACE ) )
			{
				soundPlay = Sound( L"Sounds\\arkpad.wav" );
				soundPlay.StopAll( );
				soundPlay.Play( 1.0f , 0.25f );
			}
		}

		paddle.wallCollision(wall.getWall());

		int i = 0;
		for ( PowerUp& power : powers )
		{
			power.update( dt );

			if ( power.paddleCollision( paddle ) )
			{
				switch ( power.getPower( ) )
				{
					case PowerUp::powers::length:
					{
						soundPowerUp = Sound( L"Sounds\\arklengthen.wav" );
						soundPowerUp.StopAll( );
						soundPowerUp.Play( 1.0f , 0.7f );
						paddle.lengthPwrUp( );
						offsetMaxMax = ( ( paddle.getRect( ).right - paddle.getRect( ).left ) / 2 ) - 15.0f;
						offsetMinMax = -offsetMaxMax;
						break;
					}
					case PowerUp::powers::bullet:
					{
						if ( !hasBullet )
						{
							power.turnOn( );
							hasBullet = true;
						}
						else
						{
							powers.erase( powers.begin( ) + i );
						}
						break;
					}
					case PowerUp::powers::balls:
					{
						if ( !hasBalls )
						{
							currBalls = 3;
							float offsetX = getOffset( -75.0f , -180.0f , 75.0f , 180.0f );
							float offsetY = getOffset( -75.0f , -180.0f , 75.0f , 180.0f );
							balls[ 1 ] = Ball( balls[ 0 ].getPosition( ) , Vec2( balls[ 0 ].getVelocity( ).x + offsetX , ( balls[ 0 ].getVelocity( ).y + offsetY ) ) );

							offsetX = getOffset( -75.0f , -180.0f , 75.0f , 180.0f );
							offsetY = getOffset( -75.0f , -180.0f , 75.0f , 180.0f );
							balls[ 2 ] = Ball( balls[ 0 ].getPosition( ) , Vec2( balls[ 0 ].getVelocity( ).x + offsetX, ( balls[ 0 ].getVelocity( ).y + offsetY) ) );

							hasBalls = true;
						}
						break;

					}
				}
			}

			if ( power.getPower( ) == PowerUp::powers::bullet )
			{
				power.updateBullets( dt , wall.getWall( ) );

				if ( power.shot( paddle , wnd.kbd , dt ) )
				{
					soundPlay = Sound( L"Sounds\\arkbullet.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , 0.25f );
				}
			}
				
			if ( power.wallCollision( wall.getWall( ) ) )
			{
				powers.erase( powers.begin( ) + i );
			}
			i++;
		}

	}
}

void Game::resetMy()
{
	destroyed = 0;
	nonBrickAmount = 0;
	indestructable = 0;
	nBrickCols = brickArray[current2dIndex][0][1];
	nBrickRows = brickArray[current2dIndex][0][0];
	nBricks = nBrickCols * nBrickRows;
	offsetMaxMax = 30.0f;
	offsetMinMax = -30.0f;
	hasBullet = false;
	hasBalls = false;

	padX = ((wall.getWall().right - wall.getWall().left) - (nBrickRows * brickWidth)) / 2;
	padY = ((wall.getWall().bottom - wall.getWall().top) - (nBrickCols * brickHeight)) / 3;

	if (padY + (nBrickCols * brickHeight) > 370.0f)
	{
		padY -= ((nBrickCols * brickHeight) + padY) - 370.0f;
	}
	topLeft = Vec2((wall.getWall().left + padX), (wall.getWall().top + padY));

	bricks.clear( );
	for ( PowerUp& e : powers )
	{
		e.bullets.clear( );
	}
	powers.clear( );

	int i = 0;
	for (int y = 0; y < nBrickCols; y++)
	{
		for (int x = 0; x < nBrickRows; x++)
		{
			if (brickArray[current2dIndex][1][i] > 0 && brickArray[current2dIndex][1][i] < 6)
			{
				bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), brickColors[(brickArray[current2dIndex][1][i]) - 1], 1, false));
			}
			else if (brickArray[current2dIndex][1][i] == 6)
			{
				bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), Colors::MakeRGB(255, 137, 0), 1, true));
				indestructable++;
			}
			else if (brickArray[current2dIndex][1][i] == 7)
			{
				bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), Colors::Gray, 2, false));
			}
			else
			{
				bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), Colors::Black, 0, false));
				nonBrickAmount++;
			}
			i++;
		}
	}
}

float Game::getOffset( )
{
	if ( Random::getRand( 0 , 1 ) == 1 )
		return ( Random::getRand( offsetMaxMin , offsetMaxMax ) );

	return ( Random::getRand( offsetMinMin , offsetMinMax ) );
}

float Game::getOffset( float minMin, float minMax, float maxMin, float maxMax )
{
	if ( Random::getRand( 0 , 1 ) == 1 )
		return ( Random::getRand( maxMin , maxMax ) );

	return ( Random::getRand( minMin , minMax ) );
}

void Game::ComposeFrame()
{
	wall.draw(gfx);

	for ( int i = 0; i < currBalls; i++ )
	{
		balls[ i ].draw( gfx );
	}

	for (const Brick& brick : bricks)
	{
		brick.draw(gfx);
	}

	for ( PowerUp& power : powers)
	{
		power.draw(gfx);

		if ( power.getPower( ) == PowerUp::powers::bullet )
		{
			power.drawBullets( gfx );
		}
	}

	paddle.draw(gfx);

}
