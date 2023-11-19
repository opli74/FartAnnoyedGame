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
#include "GameState.h"
#include "GameLevel.h"
#include <random>
#include <string>
#include <map>

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

	/********************************/
	/*  User Functions              */

	//logic
	float getOffset( );
	float getOffset( float minMin , float minMax , float maxMin , float maxMax );

	std::string removeTail( std::string& str );

	void playSound( Sound& sound , std::wstring file , float vol );
	void playSound( Sound& sound , std::wstring file , float vol , float start , float end );
	
	void checkCollision( Brick& brick , int i , bool& collisionHappened , float& collisionDistSq , int& collisionIndex , int& ballIndex , float dt );
	void collisionHasHappened( std::vector< Brick >& bricks , int collisionIndex , int ballIndex , bool sound );

	Color lightenCol( const Color& in , float amount );
	Color darkenCol( const Color& in , float amount );


	enum class GameMenuOption
	{
		Easy,
		Medium,
		Hard,
		Create,
	};


	void handleGameMenuSelection(GameMenuOption option, float dt );
	void handleCreateMenuSelection();
	void handleHoveredBox( Box& box, GameMenuOption option );
	void handleUnhoveredBox(Box& box, GameMenuOption option);
	void configureGameParameters(int frequency, float ballSpeed);

	//powerups!
	void handleLengthPowerUp(Paddle& paddle);
	void handleBulletPowerUp(PowerUp& power, size_t powerIndex);
	void handleBallsPowerUp();
	void handleBlockPowerUp();
	void handleBombPowerUp();
	void handleBulletPowerUpBehavior(PowerUp& power, float dt);

	//level stff
	void initializeLevel(const std::tuple<int, int>& dimensions);
	void resetObjectsPositions();
	void initializeWallPadding();
	void initializeBricks(const std::vector<std::vector<int>>& gameBricks, bool drawSpaceBricks);
	void levelChange( const std::vector< std::vector<int> >& bricks , const std::tuple<int , int>& dimensions , bool drawSpaceBricks = false );

	//drawing
	void drawTimeFormat( float time , Vec2 pos , int size );
	void drawScore( );
	void drawTitle( );

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables  */
	GameState state = GameState::GAME_MENU;

	static constexpr int screenHalfWidth = 400;
	static constexpr int screenHalfHeight = 300;

	static constexpr int screenThirdWidth = 267;
	static constexpr int screenThirdHeight = 200;
	static constexpr int screen2ThirdWidth = 534;
	static constexpr int screen2ThirdHeight = 400;

	static constexpr int screenQuarterWidth = 200;
	static constexpr int screen3QuarterWidth = 600;

	int shotCount = 0;
	int lives = 6;
	std::string scoreText = "you win";

	//to keep track of volumes
	float soundEffectVol = 0.3f;
	float musicVol = 0.2f;

	//boxes for main menu
	float boxW = 125.0f , boxH = 35.0f;

	bool playSoundOnce = true;

	Color boxLight = Colors::LightGray , menuBoxCol = Colors::MakeRGB( 20 , 20 , 20 );

	Rect easy = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 - 120 ) , boxW , boxH );
	Rect medium = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 - 20 ) , boxW , boxH );
	Rect hard = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 + 80 ) , boxW , boxH );
	Rect create = Rect::fromCenter( Vec2( gfx.ScreenWidth / 2 , gfx.ScreenHeight / 2 + 160 ) , boxW - 15 , boxH - 15 );

	std::map<int , Box> menuBoxes = {
		{ 0, Box( easy , Colors::White , menuBoxCol , Colors::White , "easy" , 4 , 2 ) },
		{ 1, Box( medium , Colors::White , menuBoxCol , Colors::White , "medium" , 4 , 2 ) } ,
		{ 2, Box( hard , Colors::White , menuBoxCol , Colors::Red , "hard" , 4 , 2 ) },  
		{ 3, Box( create , Colors::White , menuBoxCol , Colors::White , "create" , 3 , 2 ) }
	};

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

	//boxes for Create screen
	int num = -1;

	//return box
	Rect returnRectGame = Rect::fromCenter( Vec2( 745.0f , gfx.ScreenHeight / 2 ) , 50.0f , 15.0f );
 	Box returnBoxGame = Box( returnRectGame , Colors::White, menuBoxCol , Colors::White, "return", 2 , 2);

	Rect returnRectScore = Rect::fromCenter( Vec2( screenHalfWidth , screen2ThirdHeight + 45) , 75.0f , 20.0f );
	Box returnBoxScore = Box( returnRectScore , Colors::White , menuBoxCol , Colors::White , "return" , 3 , 2 );

	bool returnHover = false;

	Vec2 mouse;

	bool start = false , spaceClicked = false , f = false , brickAnim = true , scoreFlickerAnim = false, createScreen = false;

	int powerFreq = 8;

	float timeDraw = 0.0f;
	float time = 0.0f;

	int maxShots = 0;

	static constexpr float brickWidth = 42.0f;
	static constexpr float brickHeight = 20.0f;

	int nBrickRows;
	int nBrickCols;
	int nBricks;
	std::vector < Brick > bricks;

	static constexpr int nMaxBrickRows = 17;
	static constexpr int nMaxBrickCols = 13;
	std::vector< Brick > createBricks;

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

	bool play = true;

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
	std::vector< Brick > savedBlockBricks;

	//to keep track of current level
	int currentLevel = 1;

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

	bool hasBulletPower = false, hasBalls = false, paddleHasBall = false;
	float relativeX = 0.0f;

	GameLevel levels;

	/********************************/
};