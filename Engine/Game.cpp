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


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(300.0f + 250.0f, 350.0f), Vec2(-BALL_SPEED, -BALL_SPEED)),
	wall(Rect(125.0f, 675.0f, 0.0f, 600.0f), Colors::Cyan),
	soundWall(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	paddle(Vec2(400.0f, 500.0f), 50, 10)
{
	const Color brickColors[nBrickCols] = {Colors::Red, Colors::Cyan, Colors::Green, Colors::Yellow, Colors::White, Colors::Magenta};
	const float pad = ((wall.getWall().right - wall.getWall().left) - (nBrickRows * brickWidth)) / 2;
	const Vec2 topLeft(wall.getWall().left + pad, wall.getWall().top + pad);

	for (int y = 0; y < nBrickCols; y++)
	{
		const Color c = brickColors[y];
		for (int x = 0; x < nBrickRows; x++)
		{
			bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), c);
		}
	}
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

	ball.update(dt);
	paddle.update(wnd.kbd, dt);

	if (ball.wallCollision(wall.getWall()))
	{
		soundWall.Play();
	}

	bool collisionHappened = false;
	float collisionDisSq;
	int collisionIndex;

	for (int i = 0; i < nBricks; i++)
	{
		if (bricks[i].isCollidingBall(ball))
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
			soundBrick.Play();
		}
	}

	if (collisionHappened)
	{
		bricks[collisionIndex].executeBallCollision(ball);
		collisionHappened = false;
	}

	if (paddle.ballCollision(ball))
	{
		soundBrick.Play();
	}

	paddle.wallCollision(wall.getWall());

}

void Game::ComposeFrame()
{

	wall.draw(gfx);
	ball.draw(gfx);

	for (const Brick& brick : bricks)
	{
		brick.draw(gfx);
	}

	paddle.draw(gfx);


}
