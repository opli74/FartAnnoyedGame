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
	ball(Vec2(300.0f, 300.0f), Vec2(300.0f, 300.0f)),
	wall(0.0f, 800.0f, 0.0f, 600.0f),
	soundWall(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	paddle(Vec2(400.0f, 500.0f), 50, 15)
{
	const Color brickColors[nBrickCols] = {Colors::Red, Colors::Blue, Colors::Green, Colors::Yellow};

	const Vec2 topLeft(0.0f, 0.0f);

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
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	ball.update(dt);
	paddle.update(wnd.kbd, dt);

	if (ball.wallCollision(wall))
	{
		soundWall.Play();
	}

	for (Brick& brick : bricks)
	{
		if (brick.isCollidingBall(ball))
		{
			soundBrick.Play();
			break;
		}
	}

	paddle.ballCollision(ball);
	paddle.wallCollision(wall);
	
	
}

void Game::ComposeFrame()
{

	ball.draw(gfx);

	for (const Brick& brick : bricks)
	{
		brick.draw(gfx);
	}

	paddle.draw(gfx);

}
