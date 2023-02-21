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
#include "Screen.h"
#include "PowerUp.h"

#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	void reset();
	void checkPower( );
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables  */
	bool start = false, spaceClicked = false, collisionHappenedGlobal = false;

	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 18.0f;
	int nBrickRows;
	int nBrickCols;
	int nBricks;
	std::vector<Brick> bricks;
	std::vector<PowerUp> powers;
	Ball ball;
	FrameTimer ft;
	Wall wall;
	Sound soundWall;
	Sound soundBrick;
	Paddle paddle;
	Mouse mouse;
	Screen firstLevel, secondLevel;

	int current2dIndex = 0;

	bool pressed = false;

	int destroyed = 0;
	int indestructable = 0;
	int nonBrickAmount = 0;
	static constexpr Color brickColors[5] = { Colors::Red, Colors::Cyan, Colors::Green, Colors::Yellow, Colors::Magenta };
	float padX;
	float padY;
	Vec2 topLeft;

	std::vector<std::vector<std::vector<int>>> brickArray = {

		{ 
			{11, 5},

			{
			0, 0, 1, 0, 1, 7, 1, 0, 1, 0, 0,
			2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 2,
			0, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0,
			4, 4, 0, 4, 0, 7, 0, 4, 0, 4, 4,
			0, 0, 5, 0, 5, 5, 5, 0, 5, 0, 0,
			}

		},

		{
			{11, 15},

			{
			0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0,
			0, 1, 2, 7, 0, 0, 0, 7, 3, 4, 0,
			7, 2, 3, 4, 5, 0, 2, 3, 4, 5, 7,
			7, 3, 4, 5, 1, 2, 3, 4, 5, 1, 7,
			0, 4, 5, 1, 2, 3, 4, 5, 1, 2, 0,
			0, 0, 1, 2, 3, 4, 5, 1, 2, 0, 0,
			0, 0, 2, 3, 4, 5, 1, 2, 3, 0, 0,
			6, 0, 0, 4, 5, 1, 2, 3, 0, 0, 6,
			0, 0, 0, 5, 1, 2, 3, 4, 0, 0, 0,
			0, 0, 0, 0, 2, 3, 4, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0,
			}

		},

		{
			{11, 17},

			{
			0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 
			0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 
			0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 
			0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 
			0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 
			0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 
			0, 7, 7, 1, 7, 7, 7, 1, 7, 7, 0, 
			0, 7, 7, 1, 7, 7, 7, 1, 7, 7, 0, 
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
			7, 0, 7, 7, 7, 7, 7, 7, 7, 0, 7, 
			7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 
			7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 
			7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 
			0, 0, 0, 7, 7, 0, 7, 7, 0, 0, 0, 
			0, 0, 0, 7, 7, 0, 7, 7, 0, 0, 0,
			}

		}
	};
	/********************************/
};