/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Brick.h"
#include "Ball.h"
#include "FrameTimer.h"
#include "Sound.h"
#include "Paddle.h"
#include "Wall.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	bool timer(float dt, bool& operations, float amountTime);
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables  */
	bool start = false, spaceClicked = false;
	float time = 0.0f;
	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 18.0f;
	static constexpr int nBrickRows = 11;
	static constexpr int nBrickCols = 12;
	static constexpr int nHardBricks = 3;
	static constexpr int nBricks = (nBrickRows * nBrickCols) + nHardBricks;
	Brick bricks[nBricks];
	Ball ball;
	FrameTimer ft;
	Wall wall;
	Sound soundWall;
	Sound soundBrick;
	Paddle paddle;
	Mouse mouse;
	static constexpr int brickArray[nBricks] = {
		0, 1, 2, 3, 0, 0, 0, 2, 3, 4, 0,
		1, 2, 3, 4, 5, 0, 2, 3, 4, 5, 1,
		2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
		0, 4, 5, 1, 2, 3, 4, 5, 1, 2, 0,
		0, 0, 1, 2, 3, 4, 5, 1, 2, 0, 0,
		0, 0, 2, 3, 4, 5, 1, 2, 3, 0, 0,
		0, 0, 0, 4, 5, 1, 2, 3, 0, 0, 0,
		0, 0, 0, 5, 1, 2, 3, 4, 0, 0, 0,
		0, 0, 0, 0, 2, 3, 4, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0,
		
	};
	/********************************/
};