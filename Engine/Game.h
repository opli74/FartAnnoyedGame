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
#include "Timer.h"
#include "Box.h"
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
	void changeLevel();
	void scoreScreenChange( );
	void menuScreenChange( );
	float getOffset( );
	float getOffset( float minMin , float minMax , float maxMin , float maxMax );
	std::string removeTail( std::string& str );
	void drawTimeFormat( float time , Vec2 pos, int size);

	template <size_t r, size_t c>
	void checkCollision( const int( &bricks_in )[ r ][ c ] , int bricksNum , bool& collisionHappened , float& collisionDistSq, int& collisionIndex, float dt)
	{
		for ( int i = 0; i < scoreBricksCols * scoreBricksRows; i++ )
		{
			bricks[ i ].color( dt );
			if ( bricks[ i ].isCollidingBall( balls[ 0 ] ) )
			{
				if ( bricks_in[ 0 ][ i ] != 0 )
				{
					const float newCollisionDistSq = ( balls[ 0 ].getPosition( ) - bricks[ i ].getRect( ).getCenter( ) ).GetLengthSq( );
					if ( collisionHappened )
					{
						if ( newCollisionDistSq < collisionDistSq )
						{
							collisionDistSq = newCollisionDistSq;
							collisionIndex = i;
						}
					}
					else
					{
						collisionDistSq = newCollisionDistSq;
						collisionIndex = i;
						collisionHappened = true;
					}
				}
			}
		}
	};

	void collisionHasHappened( Brick* bricks, int collisionIndex, int ballIndex , bool sound);
	void drawScore( );

	Color lightenCol( const Color& in , float amount );
	Color darkenCol( const Color& in , float amount );
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables  */
	static constexpr int screenHalfWidth = 400;
	static constexpr int screenHalfHeight = 300;

	static constexpr int screenThirdWidth = 267;
	static constexpr int screenThirdHeight = 200;
	static constexpr int screen2ThirdWidth = 534;
	static constexpr int screen2ThirdHeight = 400;

	static constexpr int screenQuarterWidth = 200;
	static constexpr int screen3QuarterWidth = 600;

	int lives = 6;
	std::string scoreText = "you win";

	//to keep track of volumes
	float soundEffectVol = 0.3f;
	float musicVol = 0.2f;

	//boxes for main menu
	float boxW = 125.0f , boxH = 35.0f;
	bool eHover = false , mHover = false , hHover = false;

	Rect easy = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 - 100 ) , boxW , boxH );
	Rect medium = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 ) , boxW , boxH );
	Rect hard = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 + 100 ) , boxW , boxH );

	Color easyCol = Colors::LightGray , mediumCol = Colors::LightGray , hardCol = Colors::LightGray , menuBoxCol = Colors::MakeRGB( 20 , 20 , 20 );

	Box boxEasy = Box( easy , Colors::White , menuBoxCol , Colors::White , "easy" , 4 , 2 );
	Box boxMedium = Box( medium , Colors::White , menuBoxCol , Colors::White , "medium" , 4 , 2 );
	Box boxHard = Box( hard , Colors::White , menuBoxCol , Colors::Red , "hard" , 4 , 2 );

	bool soundMusicWait = false , soundMusicChange = false;

	bool boxSfxHover = false , boxMusicHover = false , boxMusicHoverActive = false, boxSfxHoverActive = false;
	Color soundBoxCol = Colors::Gray , soundVolCol = Colors::MakeRGB( 170, 170, 170);

	float soundBoxW = 75.0f, soundBoxH = 4.0f;
	Rect sfxVolRec = Rect::fromCenter( Vec2( screenQuarterWidth , 570.0f ), soundBoxW , soundBoxH );
	Rect musicVolRec = Rect::fromCenter( Vec2( screen3QuarterWidth , 570.0f ) , soundBoxW , soundBoxH );

	float sfxVolAmount = soundEffectVol * (soundBoxW * 2);
	float musicVolAmount = musicVol * ( soundBoxW * 2 );

	float soundVolBoxH = soundBoxH * 2;

	Rect sfxVolRecVol = Rect( Vec2( screenQuarterWidth - soundBoxW , 570.0f - soundBoxH) , sfxVolAmount , soundVolBoxH );
	Rect musicVolRecVol = Rect( Vec2( screen3QuarterWidth - soundBoxW , 570.0f -soundBoxH) , musicVolAmount , soundVolBoxH );

	Box boxSfx = Box( sfxVolRec , soundBoxCol );
	Box boxMusic = Box( musicVolRec , soundBoxCol );
	Box boxSfxVol = Box( sfxVolRecVol , soundVolCol );
	Box boxMusicVol = Box( musicVolRecVol , soundVolCol );

	//return box
	Rect returnRectGame = Rect::fromCenter( Vec2( 745.0f , gfx.ScreenHeight / 2 ) , 50.0f , 15.0f );
 	Box returnBoxGame = Box( returnRectGame , Colors::White, menuBoxCol , Colors::White, "return", 2 , 2);

	Rect returnRectScore = Rect::fromCenter( Vec2( screenHalfWidth , screen2ThirdHeight + 45) , 75.0f , 20.0f );
	Box returnBoxScore = Box( returnRectScore , Colors::White , menuBoxCol , Colors::White , "return" , 3 , 2 );

	bool returnHover = false;


	Vec2 mouse;

	bool start = false , spaceClicked = false , menuScreen = true , scoreScreen = false , f = false , brickAnim = true , scoreFlickerAnim = false;

	int powerFreq = 8;

	float timeDraw = 0.0f;
	float time = 0.0f;

	static constexpr float brickWidth = 42.0f;
	static constexpr float brickHeight = 20.0f;

	int nBrickRows;
	int nBrickCols;
	int nBricks;
	Brick* bricks = nullptr;

	std::vector<PowerUp> powers;

	int currBalls = 1;
	static constexpr int maxBalls = 3;
	std::vector< Ball > balls;

	FrameTimer ft;

	Wall wall;
	Wall menuWall;

	Sound soundPlay;
	Sound soundPowerUp;
	Sound soundMusic;
	Sound soundChange;

	Paddle paddle;

	Text text;

	bool song1 = true , song2 = false , song3 = false , song4 = false , play = true;
	//various timers for animations and delays
	Timer paddleCollision { 15.0f };
	Timer timerStart { 2.1f };
	Timer timerFlickerAnim { 0.25f };
	Timer menuScreenWait { 0.5f };
	Timer songOne { 180.0f };
	Timer songTwo { 125.0f };
	Timer songThree { 125.0f };
	Timer songFour { 125.0f };

	//powerup bricks for when the block powerup is used
	float blockBricksY;
	float blockBricksX;
	int blockBricksCurr = 0;
	Brick* blockBricks = nullptr;

	//to keep track of current level
	int current2dIndex = 0;

	//score draw is used to animate score, score keeps the score duh...
	int score = 0;
	int scoreDraw = 0;

	bool pressed = false;

	//the starting offsets for when starting round 1
	float offset = 0.0f;
	float offsetMinMin = -10.0f;
	float offsetMinMax = -25.0f;
	float offsetMaxMin = 10.0f;
	float offsetMaxMax = 25.0f;

	//for checking if no more bricks are left to move onto next level
	int destroyed = 0;
	int indestructable = 0;
	int nonBrickAmount = 0;

	//the colours of bricks
	static constexpr Color brickColors[5] = { Colors::Red, Colors::Cyan, Colors::Green, Colors::Yellow, Colors::Magenta };
	float padX;
	float padY;
	Vec2 topLeft;

	bool hasBullet = false, hasBalls = false, paddleHasBall = false;
	float relativeX = 0.0f;


	//score screen bricks and variables
	static constexpr int scoreBricksCols = 12;
	static constexpr int scoreBricksRows = 17;
	static constexpr int nScoreBricks = scoreBricksRows * scoreBricksCols;
	static constexpr int scoreBricks[ 1 ][ 250 ] =
	{
		{
			0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
			0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0,
		}
	};


	//menu bricks map and varibales
	static constexpr int menuBricksCols = 12;
	static constexpr int menuBricksRows = 17;
	static constexpr int nMenuBricks = menuBricksCols * menuBricksRows;
	static constexpr int mainMenuBricks[ 1 ][ 250 ] =
	{
		{
			6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6,
			6, 1, 2, 3, 6, 0, 0, 0, 0, 0, 0, 0, 6, 1, 2, 3, 6,
			6, 2, 3, 4, 6, 0, 0, 0, 0, 0, 0, 0, 6, 2, 3, 4, 6,
			6, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 6, 3, 4, 5, 6,
			6, 4, 5, 1, 6, 0, 0, 0, 0, 0, 0, 0, 6, 4, 5, 1, 6,
			6, 5, 1, 2, 6, 0, 0, 0, 0, 0, 0, 0, 6, 5, 1, 2, 6,
			6, 1, 2, 3, 6, 0, 0, 0, 0, 0, 0, 0, 6, 1, 2, 3, 6,
			6, 2, 3, 4, 6, 0, 0, 0, 0, 0, 0, 0, 6, 2, 3, 4, 6,
			6, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 6, 3, 4, 5, 6,
			6, 4, 5, 1, 6, 0, 0, 0, 0, 0, 0, 0, 6, 4, 5, 1, 6,
			6, 5, 1, 2, 6, 0, 0, 0, 0, 0, 0, 0, 6, 5, 1, 2, 6,
			6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6,
		}
	};


	//the brick maps for the bricks displayed in each level, the first array is two numbers that define the amount of rows and column.
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
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
			}
		}
	};
	/********************************/
};