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

	int getInt(int min, int max)
	{
		std::uniform_int_distribution<int> die(min, max);
		return die(mt);
	}
}

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	wall(Rect(110.0f, 690.0f, 0.0f, 600.0f), Colors::MakeRGB(150,150,150)),
	paddle( Vec2( 400.0f , 500.0f ) , 50 , 8 )
	
{
	offset = float( Random::getInt( offsetMin , offsetMax ) );
	ball = Ball( Vec2( 400.0f + offset, ( 500.0f - 15.0f ) ) , Vec2( BALL_SPEED , BALL_SPEED ) );

	soundPlay = Sound( L"Sounds\\arkstart.wav" );
	soundPlay.StopAll( );
	soundPlay.Play( 1.0f , 0.2f );

	resetMy( );
	
	firstLevel.makeActive();
}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
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
			offset = float( Random::getInt( offsetMin , offsetMax ) );
			ball.switchRestart();
			ball.setPosition(Vec2(400.0f + offset , 500.0f - 15.0f));
			paddle.setPos(Vec2(400.0f, 500.0f));

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
			offset = float( Random::getInt( offsetMin , offsetMax ) );
			ball.switchRestart();
			ball.setPosition(Vec2(400.0f + offset, 500.0f - 15.0f));
			paddle.setPos(Vec2(400.0f, 500.0f));

			if (current2dIndex < 2)
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
		if (!spaceClicked)
			ball.setPosition(Vec2(paddle.getVec().x + offset , 500.0f - 15.0f));

		if ( wnd.kbd.KeyIsPressed( VK_SPACE ) && !spaceClicked )
		{
			spaceClicked = true;
			soundPlay = Sound( L"Sounds\\arkpad.wav" );
			soundPlay.StopAll( );
			soundPlay.Play( 1.0f , 0.25f );
		}

		if (spaceClicked)
			ball.update(dt);

		paddle.update(wnd.kbd, dt);

		ball.wallCollision( wall.getWall( ) );

		if (ball.getRestart())
		{
			ball.switchRestart();
			ball.setPosition(Vec2(400.0f + offset, 500.0f - 15.0f));
			paddle.setPos(Vec2(400.0f, 500.0f));
			start = false;
			spaceClicked = false;

		}

		bool collisionHappened = false;
		float collisionDisSq;
		int collisionIndex = 0;

		for (int i = 0; i < nBricks; i++)
		{
			bricks[i].color();
			if (bricks[i].isCollidingBall(ball))
			{
				if (brickArray[current2dIndex][1][i] != 0)
				{
					const float newCollisionDistSq = (ball.getPosition() - bricks[i].getRect().getCenter()).GetLengthSq();
					if (collisionHappened)
					{
						if (newCollisionDistSq < collisionDisSq)
						{
							collisionDisSq = newCollisionDistSq;
							collisionIndex = i;
						}
					}
					else
					{
						collisionDisSq = newCollisionDistSq;
						collisionIndex = i;
						collisionHappened = true;
					}
				}
			}
			for ( PowerUp& power : powers )
			{
				for ( int f = 0; f < power.bullets.size(); f++ )
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

			if ( !wnd.kbd.KeyIsPressed( VK_SPACE ) )
			{
				soundPlay.StopAll( );
				soundPlay.Play( 1.0f , 0.25f );
			}

			bricks[ collisionIndex ].executeBallCollision( ball );
			
			if (bricks[collisionIndex].getDestroyed())
			{
				if ( powers.size( ) == 0 )
				{
					if ( Random::getInt( 1 , 2 ) == 1 )
					{
						powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) ) );
					}
				}
				destroyed++;
			}
				
			bricks[collisionIndex].hit = true;
			collisionHappenedGlobal = true;
		}

		/*paddle.ballCollision( ball );*/
		if (paddle.ballCollision(ball) &&  !wnd.kbd.KeyIsPressed( VK_SPACE )  )
		{
			soundPlay = Sound( L"Sounds\\arkpad.wav" );
			soundPlay.StopAll( );
			soundPlay.Play( 1.0f , 0.25f );
		}

		paddle.wallCollision(wall.getWall());

		int i = 0;
		for ( PowerUp& power : powers )
		{
			power.update( dt );


			if ( power.paddleCollision( paddle ) )
				power.givePower( );

			if ( power.getPower( ) )
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
				power.bullets.clear( ); 
				powers.erase( powers.begin( ) + i );
			}
			i++;
		}

	}
	else
	{
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

	padX = ((wall.getWall().right - wall.getWall().left) - (nBrickRows * brickWidth)) / 2;
	padY = ((wall.getWall().bottom - wall.getWall().top) - (nBrickCols * brickHeight)) / 3;

	if (padY + (nBrickCols * brickHeight) > 350.0f)
	{
		padY -= ((nBrickCols * brickHeight) + padY) - 350.0f;
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



void Game::ComposeFrame()
{

	wall.draw(gfx);
	ball.draw(gfx);

	for (const Brick& brick : bricks)
	{
		brick.draw(gfx);
	}

	for ( PowerUp& power : powers)
	{
		power.draw(gfx);

		if ( power.getPower( ) )
		{
			power.drawBullets( gfx );
		}
	}

	paddle.draw(gfx);

}
