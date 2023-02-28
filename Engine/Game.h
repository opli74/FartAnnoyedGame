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
#include "SoundEffect.h"
#include "Text.h"
#include <random>
#include <string>

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
	void resetMy();
	float getOffset( );
	float getOffset( float minMin , float minMax , float maxMin , float maxMax );
	std::string removeTail( std::string& str );
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables  */
	bool start = false , spaceClicked = false;

	float time = 0.0f;

	static constexpr float brickWidth = 42.0f;
	static constexpr float brickHeight = 20.0f;
	int nBrickRows;
	int nBrickCols;
	int nBricks;
	/*std::vector<Brick> bricks;*/
	Brick* bricks = nullptr;
	std::vector<PowerUp> powers;
	int currBalls = 1;
	static constexpr int maxBalls = 3;
	Ball balls[ maxBalls ];
	FrameTimer ft;
	Wall wall;
	Sound soundPlay;
	Sound soundPowerUp;
	Paddle paddle;
	Mouse mouse;
	Text text;

	std::string txt = "abcdefghijklmnopqrstuvwxyz";
	std::string nums = "0123456789";

	int current2dIndex = 0;

	bool pressed = false;

	float offset = 0.0f;
	float offsetMinMin = -10.0f;
	float offsetMinMax = -25.0f;
	float offsetMaxMin = 10.0f;
	float offsetMaxMax = 25.0f;

	int destroyed = 0;
	int indestructable = 0;
	int nonBrickAmount = 0;
	static constexpr Color brickColors[5] = { Colors::Red, Colors::Cyan, Colors::Green, Colors::Yellow, Colors::Magenta };
	float padX;
	float padY;
	Vec2 topLeft;

	bool hasBullet = false, hasBalls = false, paddleHasBall = false;
	float relativeX = 0.0f;

	static constexpr int brickArray[ 4 ][ 2 ][ 200 ] = {

		{
			{11, 6},

			{
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
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
			0, 0, 1, 2, 3, 6, 5, 1, 2, 0, 0,
			0, 0, 2, 3, 4, 5, 1, 2, 3, 0, 0,
			1, 0, 0, 4, 5, 1, 2, 3, 0, 0, 1,
			0, 0, 0, 5, 1, 2, 3, 4, 0, 0, 0,
			0, 0, 0, 0, 2, 3, 4, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 6, 0, 0, 0, 1, 0,
			}

		},

		{
			{ 13 , 11 },

			{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			2, 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 2, 2, 2,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			2, 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			}
		}
	};
	/********************************/
};