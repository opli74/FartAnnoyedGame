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
	ball(Vec2(400.0f, 500.0f - 15.0f), Vec2(0.0f, -BALL_SPEED)),
	wall(Rect(110.0f, 690.0f, 0.0f, 600.0f), Colors::MakeRGB(150,150,150)),
	soundWall(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	paddle(Vec2(400.0f, 500.0f), 50, 8)
{

	const Color brickColors[nBrickCols] = {Colors::Red, Colors::Cyan, Colors::Green, Colors::Yellow, Colors::Magenta};
	const float pad = ((wall.getWall().right - wall.getWall().left) - (nBrickRows * brickWidth)) / 2;
	const Vec2 topLeft(wall.getWall().left + pad, (wall.getWall().top + pad * 2));

	int i = 0;
	for (int y = 0; y < nBrickCols; y++)
	{
		//const Color c = brickColors[y];
		for (int x = 0; x < nBrickRows; x++)
		{
			if (brickArray[i] == 1)
				bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), brickColors[0], 1);
			else if (brickArray[i] == 2)
				bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), brickColors[1], 1);
			else if (brickArray[i] == 3)
				bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), brickColors[2], 1);
			else if (brickArray[i] == 4)
				bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), brickColors[3], 1);
			else if (brickArray[i] == 5)
				bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), brickColors[4], 1);
			else if(brickArray[i] == 6)
				bricks[x + y * nBrickRows] = Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), Colors::MakeRGB(255, 137, 0), 1);

			i++;
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
	start = timer(dt, start, 2.0f);
	if (start)
	{
		if (!spaceClicked)
			ball.setPosition(Vec2(paddle.getVec().x, 500.0f - 15.0f));
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
				spaceClicked = true;

		if (spaceClicked)
			ball.update(dt);

		paddle.update(wnd.kbd, dt);

		if (ball.wallCollision(wall.getWall()) == 1)
		{
			soundWall.Play();
		}

		if (ball.getRestart())
		{
			ball.switchRestart();
			ball.setPosition(Vec2(400.0f, 500.0f - 15.0f));
			ball.setDirection(Vec2(BALL_SPEED, BALL_SPEED));
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
				if (brickArray[i] != 0)
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
		}

		if (collisionHappened)
		{
			if (brickArray[collisionIndex] <= 5)
				bricks[collisionIndex].executeBallCollision(ball, false);

			else if (brickArray[collisionIndex] == 6)
				bricks[collisionIndex].executeBallCollision(ball, true);
			
			bricks[collisionIndex].hit = true;
			collisionHappened = false;
		}

		if (paddle.ballCollision(ball))
		{
			soundBrick.Play();
		}

		paddle.wallCollision(wall.getWall());

	}

}

bool Game::timer(float dt, bool& operations, float amountTime)
{
	amountTime = amountTime * 60.0f;
	if (!operations)
	{
		time += dt * 60.0f;

		if (time >= amountTime)
		{
			time = 0.0f;
			return !operations;
		}

	}
	return operations;
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
