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
#include <math.h>

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


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ) ,
	gfx( wnd ) ,
	wall( Rect( 110.0f , 690.0f , 45.0f , 600.0f ) , Colors::MakeRGB( 150 , 150 , 150 ) , true) ,
	menuWall( Rect( 0.0f , 800.0f , 0.0f , 600.0f ) , Colors::MakeRGB( 150 , 150 , 150 ) ,24, 20, false ) ,
	paddle( Vec2( 400.0f , PADDLE_Y ) , PADDLE_HALF_WIDTH ,6.0f )
	
{
	offset = getOffset( );
	balls.push_back( Ball( Vec2( 400.0f + offset , ( PADDLE_Y - 12.0f ) ) , Vec2( 400.0f , 400.0f) ) );
	G_BALL_SPEED = 550.0f;

	blockBricksX = wall.getWall( ).left;
	blockBricksY = wall.getWall( ).bottom - brickHeight;
	blockBricks = new Brick[ 13 ];

	levelChange( levels.loadTiles( GameLevel::Type::Menu , 1 ) , levels.getDimensions( GameLevel::Type::Menu , 1 ) );
}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.00015f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame( );
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{

	bool collisionHappened = false;
	float collisionDisSq = 0.0f;
	int collisionIndex = 0;
	int ballIndex = 0;
	mouse = Vec2( wnd.mouse.GetPosX( ) , wnd.mouse.GetPosY( ) );

	//----------------------------MenuScreen-------------------------//
	switch ( state )
	{
		case GameState::GAME_MENU:
		{

			if ( play )
			{
				soundMusic = Sound( L"Sounds\\musicTitle.wav" , 0.0f , 34.0f );
				soundMusic.StopAll( );
				soundMusic.Play( 1.0f , musicVol );
				soundChange.StopAll( );
				play = false;
			}

			balls[ 0 ].anim( dt );
			paddle.setPos( Vec2( paddle.getVec( ).x + ( balls[ 0 ].getPosition( ).x - paddle.getVec( ).x ) / 600 * ( balls[ 0 ].getPosition( ).y / 400 ) , PADDLE_Y ) );
			paddle.wallCollision( menuWall.getWall( ) );

			balls[ 0 ].update( dt );
			balls[ 0 ].wallCollision( menuWall.getWall( ) , false );

			if ( paddle.ballCollision( balls[ 0 ] ) )
			{
				balls[ 0 ].setDirection( Vec2( getOffset( -150.0f , -G_BALL_SPEED , 150.0f , G_BALL_SPEED ) , -Random::getRand( 150.0f , G_BALL_SPEED ) ) );
			}

			int i = 0;
			for ( auto& e : bricks )
			{
				checkCollision( e , i , collisionHappened , collisionDisSq , collisionIndex , ballIndex , dt );
				i++;
			}

			if ( collisionHappened )
			{
				collisionHasHappened( bricks , collisionIndex , ballIndex , false );
			}

			if ( !menuScreenWait.checkTime( ) )
				menuScreenWait.update( dt );

			if ( boxEasy.isHover( mouse ) )
			{
				if ( wnd.mouse.LeftIsPressed( ) && menuScreenWait.checkTime( ) )
				{
					soundChange = Sound( L"Sounds\\screenChange.wav" );
					soundChange.StopAll( );
					soundChange.Play( 1.0f , soundEffectVol );

					soundMusic.StopAll( );

					play = true;

					powerFreq = 5;
					G_BALL_SPEED = 375.0f;
					balls[ 0 ].update( dt );
					paddle.setSpeed( );
					state = GameState::GAME_ACTIVE;
					levelChange( levels.loadTiles( GameLevel::Type::Game , currentLevel ) , levels.getDimensions( GameLevel::Type::Game , currentLevel ) );
				}

				if ( !eHover )
				{
					boxEasy.setFill( Colors::White );
					boxEasy.setBorder( Colors::Red );
					boxEasy.setTextCol( Colors::Black );
					boxEasy.setTextSize( 5 );

					soundPlay = Sound( L"Sounds\\button.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
				}
				eHover = true;
			}
			else
			{
				eHover = false;
				boxEasy.setFill( menuBoxCol );
				boxEasy.setBorder( Colors::White );
				boxEasy.setTextCol( Colors::White );
				boxEasy.setTextSize( 4 );
			}

			if ( boxMedium.isHover( mouse ) )
			{
				if ( wnd.mouse.LeftIsPressed( ) && menuScreenWait.checkTime( ) )
				{
					soundChange = Sound( L"Sounds\\screenChange.wav" );
					soundChange.StopAll( );
					soundChange.Play( 1.0f , soundEffectVol );

					soundMusic.StopAll( );

					play = true;

					powerFreq = 6;
					G_BALL_SPEED = 465.0f;
					paddle.setSpeed( );
					state = GameState::GAME_ACTIVE;
					levelChange( levels.loadTiles( GameLevel::Type::Game , currentLevel ) , levels.getDimensions( GameLevel::Type::Game , currentLevel ) );
				}

				if ( !mHover )
				{
					boxMedium.setFill( Colors::White );
					boxMedium.setBorder( Colors::Red );
					boxMedium.setTextCol( Colors::Black );
					boxMedium.setTextSize( 5 );

					soundPlay = Sound( L"Sounds\\button.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
				}
				mHover = true;
			}
			else
			{
				mHover = false;
				boxMedium.setFill( menuBoxCol );
				boxMedium.setBorder( Colors::White );
				boxMedium.setTextCol( Colors::White );
				boxMedium.setTextSize( 4 );
			}

			if ( boxHard.isHover( mouse ) )
			{
				if ( wnd.mouse.LeftIsPressed( ) && menuScreenWait.checkTime( ) )
				{
					soundChange = Sound( L"Sounds\\screenChange.wav" );
					soundChange.StopAll( );
					soundChange.Play( 1.0f , soundEffectVol );

					soundMusic.StopAll( );

					play = true;

					powerFreq = 8;
					G_BALL_SPEED = 555.0f;
					paddle.setSpeed( );
					state = GameState::GAME_ACTIVE;
					levelChange( levels.loadTiles( GameLevel::Type::Game , currentLevel ) , levels.getDimensions( GameLevel::Type::Game , currentLevel ) );
				}

				if ( !hHover )
				{
					soundPlay = Sound( L"Sounds\\button.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
					boxHard.setFill( Colors::White );
					boxHard.setBorder( Colors::Red );
					boxHard.setTextCol( Colors::Black );
					boxHard.setTextSize( 5 );
				}
				hHover = true;
			}
			else
			{
				hHover = false;
				boxHard.setFill( menuBoxCol );
				boxHard.setBorder( Colors::White );
				boxHard.setTextCol( Colors::Red );
				boxHard.setTextSize( 4 );
			}

			if ( boxCreate.isHover( mouse ) )
			{
				if ( wnd.mouse.LeftIsPressed( ) && menuScreenWait.checkTime( ) )
				{
					soundChange = Sound( L"Sounds\\screenChange.wav" );
					soundChange.StopAll( );
					soundChange.Play( 1.0f , soundEffectVol );

					soundMusic.StopAll( );

					state = GameState::GAME_CREATE;

				}

				if ( !cHover )
				{
					boxCreate.setFill( Colors::White );
					boxCreate.setBorder( Colors::Red );
					boxCreate.setTextCol( Colors::Black );
					boxCreate.setTextSize( 3 );
					soundPlay = Sound( L"Sounds\\button.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
				}
				cHover = true;
			}
			else
			{
				cHover = false;
				boxCreate.setFill( menuBoxCol );
				boxCreate.setBorder( Colors::White );
				boxCreate.setTextCol( Colors::White );
				boxCreate.setTextSize( 3 );
			}

			if ( wnd.mouse.LeftIsPressed( ) )
			{
				if ( !boxMusicHoverActive )
				{
					if ( boxMusicHover )
						boxMusicHoverActive = true;
					else
						boxMusicHoverActive = false;
				}
				else if ( boxMusicHoverActive )
				{
					musicVol = ( mouse.x - ( screen3QuarterWidth - soundBoxW ) ) / ( soundBoxW * 2 );

					if ( musicVol < 0.0f )
						musicVol = 0.0f;
					else if ( musicVol > 1.0f )
						musicVol = 1.0f;

					musicVolAmount = musicVol * ( soundBoxW * 2 );
					boxMusicVol.setRect( Rect( Vec2( screen3QuarterWidth - soundBoxW , 570.0f - soundBoxH ) , musicVolAmount , soundVolBoxH ) );

					soundMusicChange = true;
				}
				if ( !boxSfxHoverActive )
				{
					if ( boxSfxHover )
						boxSfxHoverActive = true;
					else
						boxSfxHoverActive = false;
				}
				else if ( boxSfxHoverActive )
				{
					soundEffectVol = ( mouse.x - ( screenQuarterWidth - soundBoxW ) ) / ( soundBoxW * 2 );

					if ( soundEffectVol < 0.0f )
						soundEffectVol = 0.0f;
					else if ( soundEffectVol > 1.0f )
						soundEffectVol = 1.0f;

					sfxVolAmount = soundEffectVol * ( soundBoxW * 2 );
					boxSfxVol.setRect( Rect( Vec2( screenQuarterWidth - soundBoxW , 570.0f - soundBoxH ) , sfxVolAmount , soundVolBoxH ) );
				}
			}
			else
			{
				if ( soundMusicChange )
				{
					soundMusic.StopAll( );
					soundMusic.Play( 1.0f , musicVol );
					soundMusicChange = false;
				}
				boxMusicHoverActive = false;
				boxSfxHoverActive = false;

				boxSfx.setFill( soundBoxCol );
				boxSfxVol.setFill( soundVolCol );

				boxMusic.setFill( soundBoxCol );
				boxMusicVol.setFill( soundVolCol );
			}

			if ( boxSfx.isHover( mouse ) )
			{
				boxSfxHover = true;

				boxSfx.setFill( lightenCol( soundBoxCol , 0.2f ) );
				boxSfxVol.setFill( lightenCol( soundVolCol , 1.0f ) );
			}
			else
			{
				boxSfxHover = false;
			}
			if ( boxMusic.isHover( mouse ) )
			{
				boxMusicHover = true;

				boxMusic.setFill( lightenCol( soundBoxCol , 0.2f ) );
				boxMusicVol.setFill( lightenCol( soundVolCol , 1.0f ) );
			}
			else
			{
				boxMusicHover = false;
			}
			break;
		}
		case GameState::GAME_SCORE:
		{
			if ( play )
			{
				soundMusic.StopAll( );
				timerStart.update( dt );
				G_BALL_SPEED = 550.0f;
				if ( timerStart.checkTime( ) )
				{
					soundMusic = Sound( L"Sounds\\musicTitle.wav" , 0.0f , 34.0f );
					soundMusic.StopAll( );
					soundMusic.Play( 1.0f , musicVol );
					play = false;
					scoreDraw = score;
					scoreFlickerAnim = true;
					timerStart.reset( );
					timerStart.setState( false );
				}
				else
				{
					scoreDraw = int( ( timerStart.getTime( ) / timerStart.getMaxTime( ) ) * score );
					timeDraw = ( timerStart.getTime( ) / timerStart.getMaxTime( ) ) * time;
				}
			}

			if ( returnBoxScore.isHover( mouse ) )
			{
				if ( wnd.mouse.LeftIsPressed( ) )
				{
					levelChange( levels.loadTiles( GameLevel::Type::Menu , currentLevel ) , levels.getDimensions( GameLevel::Type::Menu , currentLevel ) );
					state = GameState::GAME_MENU;
					soundChange.StopAll( );
					menuScreenWait.reset( );
					play = true;
				}

				if ( !returnHover )
				{
					soundPlay = Sound( L"Sounds\\button.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
					returnBoxScore.setFill( Colors::White );
					returnBoxScore.setBorder( Colors::Red );
					returnBoxScore.setTextCol( Colors::Black );
				}
				returnHover = true;
			}
			else
			{
				returnHover = false;
				returnBoxScore.setFill( menuBoxCol );
				returnBoxScore.setBorder( Colors::White );
				returnBoxScore.setTextCol( Colors::White );
			}

			if ( scoreFlickerAnim )
			{
				timerFlickerAnim.update( dt );
				if ( timerFlickerAnim.checkTime( ) )
				{
					timerFlickerAnim.reset( );
					timerFlickerAnim.setState( !timerFlickerAnim.getState( ) );
				}
			}

			balls[ 0 ].anim( dt );
			paddle.setPos( Vec2( paddle.getVec( ).x + ( balls[ 0 ].getPosition( ).x - paddle.getVec( ).x ) / 600 * ( balls[ 0 ].getPosition( ).y / 300 ) , PADDLE_Y ) );
			paddle.wallCollision( menuWall.getWall( ) );

			balls[ 0 ].update( dt );
			balls[ 0 ].wallCollision( menuWall.getWall( ) , false );

			if ( paddle.ballCollision( balls[ 0 ] ) )
			{
				balls[ 0 ].setDirection( Vec2( getOffset( -150.0f , -G_BALL_SPEED , 150.0f , G_BALL_SPEED ) , -Random::getRand( 150.0f , G_BALL_SPEED ) ) );
			}

			int i = 0;
			for ( auto& e : bricks )
			{
				checkCollision( e , i , collisionHappened , collisionDisSq , collisionIndex , ballIndex , dt );
				i++;
			}

			if ( collisionHappened )
			{
				collisionHasHappened( bricks , collisionIndex , ballIndex , false );
			}
			break;
		}
		case GameState::GAME_ACTIVE:
		{

			if ( wnd.kbd.KeyIsPressed( '1' ) )
			{
				if ( !pressed )
				{
					if ( currentLevel > 1 )
						currentLevel -= 1;

					levelChange( levels.loadTiles( GameLevel::Type::Game , currentLevel ) , levels.getDimensions( GameLevel::Type::Game , currentLevel ) );

					pressed = true;
				}
			}
			else if ( wnd.kbd.KeyIsPressed( '2' ) || destroyed == ( nBricks - nonBrickAmount ) - indestructable )
			{
				if ( !pressed )
				{
					if ( currentLevel < 4 )
					{
						score += 250;
						currentLevel += 1;
						levelChange( levels.loadTiles( GameLevel::Type::Game , currentLevel ) , levels.getDimensions( GameLevel::Type::Game , currentLevel ) );

						soundChange = Sound( L"Sounds\\screenChange.wav" );
						soundChange.StopAll( );
						soundChange.Play( 1.0f , soundEffectVol );

						if ( blockBricksCurr > 3 )
						{
							blockBricksCurr = 3;
						}
					}
					else
					{
						scoreText = "you win";
						currentLevel = 1;
						levelChange( levels.loadTiles( GameLevel::Type::Score , currentLevel ) , levels.getDimensions( GameLevel::Type::Score , currentLevel ) );
						state = GameState::GAME_SCORE;
					}

					pressed = true;
				}
			}
			else if ( lives == 0 )
			{
				scoreText = "you lose";
				levelChange( levels.loadTiles( GameLevel::Type::Score , currentLevel ) , levels.getDimensions( GameLevel::Type::Score , currentLevel ) );
				state = GameState::GAME_SCORE;
			}
			else
			{
				pressed = false;
			}

			for ( int i = 0; i < currBalls; i++ )
			{
				balls[ i ].anim( dt );
			}

			if ( returnBoxGame.isHover( mouse ) )
			{
				if ( wnd.mouse.LeftIsPressed( ) )
				{
					currentLevel = 1;
					levelChange( levels.loadTiles( GameLevel::Type::Menu , currentLevel ) , levels.getDimensions( GameLevel::Type::Menu , currentLevel ) );
					state = GameState::GAME_MENU;
					timerFlickerAnim.setState( false );
					timerFlickerAnim.reset( );
					scoreFlickerAnim = false;
					spaceClicked = false;

					soundChange.StopAll( );
					soundMusic = Sound( L"Sounds\\musicTitle.wav" , 0.0f , 34.0f );
					soundMusic.StopAll( );
					soundMusic.Play( 1.0f , musicVol );

					G_BALL_SPEED = 550.0f;
				}

				if ( !returnHover )
				{
					soundPlay = Sound( L"Sounds\\button.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
					returnBoxGame.setFill( Colors::White );
					returnBoxGame.setBorder( Colors::Red );
					returnBoxGame.setTextCol( Colors::Black );
				}
				returnHover = true;
			}
			else
			{
				returnHover = false;
				returnBoxGame.setFill( menuBoxCol );
				returnBoxGame.setBorder( Colors::White );
				returnBoxGame.setTextCol( Colors::White );;
			}

			if ( brickAnim )
			{
				for ( int i = 0; i < nBricks; i++ )
				{
					if ( bricks[ i ].getType( ) == Brick::Type::extra ||
						 bricks[ i ].getType( ) == Brick::Type::invinc )
					{
						bricks[ i ].hit = true;
					}
				}
				for ( int i = 0; i < blockBricksCurr; i++ )
				{
					if ( blockBricks[ i ].getType( ) == Brick::Type::extra ||
						 blockBricks[ i ].getType( ) == Brick::Type::invinc )
					{
						blockBricks[ i ].hit = true;
					}
				}
				brickAnim = false;
			}

			if ( timerStart.getState( ) )
			{

				if ( play )
				{
					soundMusic = Sound( L"Sounds\\music.wav" , 0.0f, 169.0f);
					soundMusic.StopAll( );
					soundMusic.Play( 1.0f , musicVol );
					play = false;
				}

				paddle.update( wnd.kbd , dt , time );
				paddle.wallCollision( wall.getWall( ) );

				if ( !spaceClicked )
				{
					for ( int i = 0; i < currBalls; i++ )
					{
						balls[ i ].setPosition( Vec2( paddle.getVec( ).x + offset , PADDLE_Y - 12.0f ) );
					}
				}

				if ( wnd.kbd.KeyIsPressed( VK_UP ) && !spaceClicked )
				{
					spaceClicked = true;
					paddleHasBall = false;
					soundPlay = Sound( L"Sounds\\arkpad.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
				}

				if ( spaceClicked )
				{
					for ( int i = 0; i < currBalls; i++ )
					{
						balls[ i ].update( dt );
						if ( currBalls > 1 )
						{
							if ( balls[ i ].wallCollision( wall.getWall( ) , false ) )
							{
								balls.erase( balls.begin( ) + i );
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

				if ( balls[ 0 ].getRestart( ) )
				{
					offset = getOffset( );
					balls[ 0 ].switchRestart( );
					balls[ 0 ].setPosition( Vec2( 400.0f + offset , PADDLE_Y - 12.0f ) );
					balls[ 0 ].setDirection( Vec2( 0.0f , 5.0f ) );
					paddle.setPos( Vec2( 400.0f , PADDLE_Y ) );
					timerStart.setState( false );
					spaceClicked = false;
					lives--;
					soundPlay = Sound( L"Sounds\\arkrestart.wav" );
					soundPlay.StopAll( );
					soundPlay.Play( 1.0f , soundEffectVol );
				}


				for ( int i = 0; i < nBricks; i++ )
				{
					checkCollision( bricks[ i ] , i , collisionHappened , collisionDisSq , collisionIndex , ballIndex , dt );

					for ( PowerUp& power : powers )
					{
						for ( int f = 0; f < power.bullets.size( ); f++ )
						{
							if ( power.bullets[ f ].brickCollision( bricks[ i ] ) )
							{
								if ( ( bricks[ i ].getType( ) == Brick::Type::extra ||
									   bricks[ i ].getType( ) == Brick::Type::invinc ) && bricks[ i ].health > 0 )
								{
									bricks[ i ].hit = true;
								}
								if ( bricks[ i ].getDestroyed( ) )
								{
									destroyed++;
									score += 10;
								}
							}
						}
					}
				}

				bool collisionHappendBlock = false;

				for ( int i = 0; i < blockBricksCurr; i++ )
				{
					blockBricks[ i ].color( dt );
					for ( int b = 0; b < currBalls; b++ )
					{
						if ( blockBricks[ i ].isCollidingBall( balls[ b ] ) )
						{
							const float newCollisionDistSq = ( balls[ b ].getPosition( ) - blockBricks[ i ].getRect( ).getCenter( ) ).GetLengthSq( );
							if ( collisionHappendBlock )
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
								collisionHappendBlock = true;
								ballIndex = b;
							}
						}
					}
				}

				if ( collisionHappened )
				{
					collisionHasHappened( bricks , collisionIndex , ballIndex , true );

					if ( bricks[ collisionIndex ].getDestroyed( ) )
					{
						switch ( bricks[ collisionIndex ].getType( ) )
						{
							case Brick::Type::extra:
							{
								score += 30;
							}
							case Brick::Type::normal:
							{
								score += 20;
							}
						}

						if ( Random::getRand( 0 , powerFreq ) == powerFreq )
						{
							switch ( Random::getRand( 0 , 5 ) )
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
								case 4:
								{
									powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::block ) );
									break;
								}
								case 5:
								{
									powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::bomb ) );
									break;
								}
							}
						}
						destroyed++;
					}

				}
				//if ( collisionHappendBlock )
				//{
				//	collisionHasHappened( blockBricks , collisionIndex , ballIndex , true );
				//}

				for ( int i = 0; i < currBalls; i++ )
				{
					if ( paddle.ballCollision( balls[ i ] ) )
					{
						soundPlay = Sound( L"Sounds\\arkpad.wav" );
						soundPlay.StopAll( );
						soundPlay.Play( 1.0f , soundEffectVol );
					}
				}


				int i = 0;

				for ( PowerUp& power : powers )
				{
					if ( spaceClicked )
						power.update( dt );

					if ( power.paddleCollision( paddle ) )
					{
						switch ( power.getPower( ) )
						{
							score += 80;
							case PowerUp::powers::length:
							{

								soundPowerUp = Sound( L"Sounds\\arklengthen.wav" );
								soundPowerUp.StopAll( );
								soundPowerUp.Play( 1.0f , soundEffectVol );
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
								soundPowerUp = Sound( L"Sounds\\arkpower.wav" );
								soundPowerUp.StopAll( );
								soundPowerUp.Play( 1.0f , soundEffectVol );
								int tempBalls = currBalls;
								currBalls *= 2;
								for ( int i = 0; i < tempBalls; i++ )
								{
									for ( int g = 0; g < 1; g++ )
									{
										float offsetX = getOffset( -100.0f , -275.0f , 100.0f , 275.0f );
										float offsetY = getOffset( -100.0f , -275.0f , 100.0f , 275.0f );
										balls.push_back( Ball( balls[ i ].getPosition( ) , Vec2( balls[ i ].getVelocity( ).x + offsetX , balls[ i ].getVelocity( ).y + offsetY ) ) );
									}
								}
								break;
							}
							case PowerUp::powers::block:
							{
								soundPowerUp = Sound( L"Sounds\\arkpower.wav" );
								soundPowerUp.StopAll( );
								soundPowerUp.Play( 1.0f , soundEffectVol );
								if ( blockBricksCurr < 14 )
								{
									blockBricks[ blockBricksCurr ] = Brick( Rect( Vec2( blockBricksX + ( brickWidth * blockBricksCurr ) , blockBricksY ) , brickWidth , brickHeight ) , Colors::MakeRGB( 255 , 137 , 0 ) , 1 , Brick::Type::invinc );
									blockBricksCurr++;
								}
								break;
							}

							case PowerUp::powers::bomb:
							{
								score -= 150;
								lives--;
							}
						}
					}

					if ( power.getPower( ) == PowerUp::powers::bullet )
					{
						power.updateBullets( dt , wall.getWall( ) );

						if ( power.shot( paddle , wnd.kbd , dt , spaceClicked ) && shotCount < 10 )
						{
							soundPlay = Sound( L"Sounds\\arkbullet.wav" );
							soundPlay.StopAll( );
							soundPlay.Play( 1.0f , soundEffectVol );
							shotCount++;
						}
						else if ( !power.bulletExists( ) )
						{
							powers.erase( powers.begin( ) + i );
							shotCount = 0;
						}

					}

					if ( power.wallCollision( wall.getWall( ) ) )
					{
						powers.erase( powers.begin( ) + i );
					}
					i++;
				}

				time += dt;
			}
				//not game started
			else
			{
				timerStart.update( dt );
				if ( timerStart.checkTime( ) )
				{
					timerStart.reset( );
					timerStart.setState( true );
				}

				//animate flicker for "ready"
				timerFlickerAnim.update( dt );
				if ( timerFlickerAnim.checkTime( ) )
				{
					timerFlickerAnim.reset( );
					timerFlickerAnim.setState( !timerFlickerAnim.getState( ) );
				}
			}
			break;
		}
		case GameState::GAME_CREATE:
		{
			break;
		}
	}
}

//void Game::scoreScreenChange( )
//{
//	currentLevel = 0;
//	destroyed = 0;
//	nonBrickAmount = 0;
//	indestructable = 0;
//	nBrickCols = brickArray[ currentLevel ][ 0 ][ 1 ];
//	nBrickRows = brickArray[ currentLevel ][ 0 ][ 0 ];
//	nBricks = nBrickCols * nBrickRows;
//	offsetMaxMax = 30.0f;
//	offsetMinMax = -30.0f;
//	hasBullet = false;
//	hasBalls = false;
//	play = true;
//	blockBricksCurr = 0;
//
//	soundChange = Sound( L"Sounds\\screenChange.wav" );
//	soundChange.StopAll( );
//	soundChange.Play( 1.0f , soundEffectVol );
//
//	G_BALL_SPEED = 550.0f;
//
//	timerStart.setState( false );
//	timerStart.reset( );
//
//	timerFlickerAnim.setState( false );
//	timerFlickerAnim.reset( );
//	scoreFlickerAnim = false;
//	spaceClicked = false;
//
//	balls.erase( balls.begin( ) + 1 , balls.end( ) );
//	currBalls = 1;
//
//	balls[ 0 ].setPosition( Vec2( 400.0f + offset , PADDLE_Y - 12.0f ) );
//	balls[ 0 ].setDirection( Vec2( 0.0f , 5.0f ) );
//	paddle.setPos( Vec2( 400.0f , PADDLE_Y ) );
//
//	delete[ ] blockBricks;
//	blockBricks = new Brick[ 13 ];
//
//	bricks.clear( );
//	for ( PowerUp& e : powers ) { e.bullets.clear( ); }
//	powers.clear( );
//
//	/*bricks = new Brick[ nScoreBricks ];*/
//
//	int i = 0;
//	for ( int y = 0; y < scoreBricksCols; y++ )
//	{
//		for ( int x = 0; x < scoreBricksRows; x++ )
//		{
//			if ( scoreBricks[ 0 ][ i ] > 0 && scoreBricks[ 0 ][ i ] < 6 )
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( scoreBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( scoreBricksCols * brickHeight ) ) / 2.5 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , brickColors[ ( mainMenuBricks[ 0 ][ i ] ) - 1 ] , 1 , Brick::Type::normal ) );
//			}
//			else if ( scoreBricks[ 0 ][ i ] == 6 )
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( scoreBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( scoreBricksCols * brickHeight ) ) / 2.5 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::MakeRGB( 255 , 137 , 0 ) , 1 , Brick::Type::invinc ) );
//			}
//			else if ( scoreBricks[ 0 ][ i ] == 7 )
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( scoreBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( scoreBricksCols * brickHeight ) ) / 2.5 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::Gray , 2 , Brick::Type::extra ) );
//			}
//			else
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( brickWidth ) , ( brickHeight ) ) , brickWidth , brickHeight ) , Colors::Black , 0 , Brick::Type::normal ) );
//			}
//			i++;
//		}
//	}
//}

//void Game::menuScreenChange( )
//{
//	currentLevel = 0;
//	destroyed = 0;
//	nonBrickAmount = 0;
//	indestructable = 0;
//	nBrickCols = brickArray[ currentLevel ][ 0 ][ 1 ];
//	nBrickRows = brickArray[ currentLevel ][ 0 ][ 0 ];
//	nBricks = nBrickCols * nBrickRows;
//	offsetMaxMax = 30.0f;
//	offsetMinMax = -30.0f;
//	hasBullet = false;
//	hasBalls = false;
//	play = true;
//	blockBricksCurr = 0;
//	
//	soundChange.StopAll( );
//
//	G_BALL_SPEED = 550.0f;
//
//	time = 0;
//	score = 0;
//	lives = 6;
//
//	timerStart.setState( false );
//	timerStart.reset( );
//	spaceClicked = false;
//
//	menuScreenWait.setState( false );
//	menuScreenWait.reset( );
//
//	balls.erase( balls.begin( ) + 1 , balls.end( ) );
//	currBalls = 1;
//
//	balls[ 0 ].setPosition( Vec2( 400.0f + offset , PADDLE_Y - 12.0f ) );
//	balls[ 0 ].setDirection( Vec2( 0.0f , 5.0f ) );
//	paddle.setPos( Vec2( 400.0f , PADDLE_Y ) );
//
//	delete[ ] blockBricks;
//	blockBricks = new Brick[ 13 ];
//
//	bricks.clear( );
//	for ( PowerUp& e : powers )
//	{
//		e.bullets.clear( );
//	}
//	powers.clear( );
//
//	//bricks = new Brick[ menuBricksCols * menuBricksRows ];
//
//	int i = 0;
//	for ( int y = 0; y < menuBricksCols; y++ )
//	{
//		for ( int x = 0; x < menuBricksRows; x++ )
//		{
//			if ( mainMenuBricks[ 0 ][ i ] > 0 && mainMenuBricks[ 0 ][ i ] < 6 )
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( menuBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( menuBricksCols * brickHeight ) ) / 3 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , brickColors[ ( mainMenuBricks[ 0 ][ i ] ) - 1 ] , 1 , Brick::Type::normal ) );
//			}
//			else if ( mainMenuBricks[ 0 ][ i ] == 6 )
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( menuBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( menuBricksCols * brickHeight ) ) / 3 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::MakeRGB( 255 , 137 , 0 ) , 1 , Brick::Type::invinc ) );
//			}
//			else if ( mainMenuBricks[ 0 ][ i ] == 7 )
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( menuBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( menuBricksCols * brickHeight ) ) / 3 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::Gray , 2 , Brick::Type::extra ) );
//			}
//			else
//			{
//				bricks[ i ] = ( Brick( Rect( Vec2( ( gfx.ScreenWidth - ( menuBricksRows * brickWidth ) ) / 2 , ( gfx.ScreenHeight - ( menuBricksCols * brickHeight ) ) / 3 ) + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::Black , 0 , Brick::Type::normal ) );
//			}
//			i++;
//		}
//	}
//}

void Game::levelChange( const std::vector< std::vector<int> >& gameBricks , const std::tuple<int , int>& dimensions )
{
	destroyed = 0;
	nonBrickAmount = 0;
	indestructable = 0;

	offsetMaxMax = 30.0f;
	offsetMinMax = -30.0f;

	hasBullet = false;
	hasBalls = false;

	std::tie(nBrickRows, nBrickCols) = dimensions;
	nBricks = nBrickCols * nBrickRows;

	offset = getOffset( );
	balls[ 0 ].setPosition( Vec2( 400.0f + offset , PADDLE_Y - 12.0f ) );
	balls[ 0 ].setDirection( Vec2( 0.0f , 5.0f ) );
	paddle.setPos( Vec2( 400.0f , PADDLE_Y ) );
	paddle.lengthPwrUpReset( );
	brickAnim = true;

	timerStart.setState( false );
	timerStart.reset( );
	spaceClicked = false;

	balls.erase( balls.begin( ) + 1 , balls.end( ) );
	currBalls = 1;

	padX = ((wall.getWall().right - wall.getWall().left) - (nBrickRows * brickWidth)) / 2;
	padY = ((wall.getWall().bottom - wall.getWall().top) - (nBrickCols * brickHeight)) / 4;

	if (padY + (nBrickCols * brickHeight) > 340.0f)
	{
		padY -= ((nBrickCols * brickHeight) + padY) - 340.0f;
	}
	topLeft = Vec2((wall.getWall().left + padX), (wall.getWall().top + padY));

	bricks.clear( );
	for ( PowerUp& e : powers )
	{
		e.bullets.clear( );
	}
	powers.clear( );

	int y = 0 , x = 0;
	for ( auto& row : gameBricks )
	{
		for ( auto& col : row )
		{
			if ( col > 0 && col < 6 )
			{
				bricks.push_back( Brick( Rect( topLeft + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , brickColors[ ( col ) - 1 ] , 1 , Brick::Type::normal ) );
			}
			else if ( col == 6 )
			{
				bricks.push_back( Brick( Rect( topLeft + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::MakeRGB( 255 , 137 , 0 ) , 1 , Brick::Type::invinc ) );
				indestructable++;
			}
			else if ( col == 7 )
			{
				bricks.push_back( Brick( Rect( topLeft + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::Gray , 2 , Brick::Type::extra ) );
			}
			else
			{
				bricks.push_back( Brick( Rect( topLeft + Vec2( ( x * brickWidth ) , ( y * brickHeight ) ) , brickWidth , brickHeight ) , Colors::Black , 0 , Brick::Type::normal ) );
				nonBrickAmount++;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

float Game::getOffset( )
{
	if ( Random::getRand( 0 , 1 ) == 1 )
		return ( Random::getRand( offsetMaxMin , offsetMaxMax ) );
	
	float rand = Random::getRand( std::abs( offsetMinMin ) , std::abs( offsetMinMax ) );
	return -rand;
}

float Game::getOffset( float minMin, float minMax, float maxMin, float maxMax )
{
	if ( Random::getRand( 0 , 1 ) == 1 )
		return ( Random::getRand( maxMin , maxMax ) );

	float rand = Random::getRand( std::abs(minMin) , std::abs(minMax) );
	return -rand;
}

std::string Game::removeTail( std::string& str )
{
	std::string str_ = str;
	int index = 0;

	for ( int i = 0; i < str.size( ) - 1; i++ )
	{
		if ( str[ i ] == '.' )
		{
			index = i;
			break;
		}
	}

	str_.erase( str_.begin( ) + index + 2 , str_.end( ) );

	return str_;
}

void Game::drawTimeFormat( float time , Vec2 pos, int size )
{
	std::string m = std::to_string(int( time / 60 ) % 60);
	std::string ss = std::to_string( int( time ) % 60 );
	std::string ms = std::to_string( int( time * 100 ) % 100 );

	if ( ( int( time / 60 ) % 60 ) < 10 )
		m = "0" + m;

	if ( int( time ) % 60 < 10)
		ss = "0" + ss;

	if ( int( time * 100 ) % 100 < 10 )
		ms = "0" + ms;

	text.drawText( gfx ,  m + ":" + ss + ":" + ms, pos , Colors::White , size , true);

}

void Game::checkCollision( Brick& brick, int i, bool& collisionHappened , float& collisionDistSq , int& collisionIndex , int& ballIndex, float dt )
{
	brick.color( dt );
	for ( int b = 0; b < currBalls; b++ )
	{
		if ( brick.isCollidingBall( balls[ b ] ) )
		{
			const float newCollisionDistSq = ( balls[ b ].getPosition( ) - brick.getRect( ).getCenter( ) ).GetLengthSq( );
			if ( collisionHappened )
			{
				if ( newCollisionDistSq < collisionDistSq )
				{
					collisionDistSq = newCollisionDistSq;
					collisionIndex = i;
					ballIndex = b;
				}
			}
			else
			{
				collisionDistSq = newCollisionDistSq;
				collisionIndex = i;
				collisionHappened = true;
				ballIndex = b;
			}
		}
	}
}


void Game::collisionHasHappened( std::vector< Brick >& bricks , int collisionIndex , int ballIndex , bool sound)
{

	if ( bricks[ collisionIndex ].getType( ) == Brick::Type::invinc || bricks[ collisionIndex ].getType( ) == Brick::Type::extra )
	{
		soundPlay = Sound( L"Sounds\\arkstrongbrick.wav" );
	}
	else
	{
		soundPlay = Sound( L"Sounds\\arkbrick.wav" );
	}

	if ( sound )
	{
		soundPlay.StopAll( );
		soundPlay.Play( 1.0f , soundEffectVol );
	}

	bricks[ collisionIndex ].executeBallCollision( balls[ ballIndex ] );

	if ( ( bricks[ collisionIndex ].getType( ) == Brick::Type::extra ||
		   bricks[ collisionIndex ].getType( ) == Brick::Type::invinc ) && bricks[ collisionIndex ].health > 0 )
	{
		bricks[ collisionIndex ].hit = true;
	}
}

void Game::drawScore( )
{
	if ( !scoreFlickerAnim )
	{
		text.drawText( gfx , std::to_string( scoreDraw ) , Vec2( screenHalfWidth + 75 , screen2ThirdHeight - 65 ) , Colors::White , 5 , 1 );
	}
	else
	{
		if ( !timerFlickerAnim.getState( ) )
			text.drawText( gfx , std::to_string( scoreDraw ) , Vec2( screenHalfWidth + 75 , screen2ThirdHeight - 65 ) , Colors::White , 5 , 1 );
	}
}

Color Game::lightenCol( const Color& in , float amount )
{
	Color temp = in;
	temp.SetR( in.GetR( ) + unsigned char( ( float( 255u - in.GetR( ) ) * amount ) ) );
	temp.SetG( in.GetG( ) + unsigned char( ( float( 255u - in.GetG( ) ) * amount ) ) );
	temp.SetB( in.GetB( ) + unsigned char( ( float( 255u - in.GetB( ) ) * amount ) ) );
	return temp;
}

Color Game::darkenCol( const Color& in , float amount )
{
	Color temp = in;
	temp.SetR( unsigned char( float( in.GetR( ) ) * amount ) );
	temp.SetG( unsigned char( float( in.GetG( ) ) * amount ) );
	temp.SetB( unsigned char( float( in.GetB( ) ) * amount ) );
	return temp;
}


//drawing logic loop
void Game::ComposeFrame()
{
	//main menu screen
	switch ( state )
	{
		case GameState::GAME_MENU:
		{
			menuWall.draw( gfx );

			text.drawText( gfx , "Ark Annoyed" , Vec2( screenHalfWidth + 1 , ( screenHalfHeight - 240 ) + 1 ) , Colors::Red , 10 , 1 );
			text.drawText( gfx , "Ark Annoyed" , Vec2( screenHalfWidth + 2 , ( screenHalfHeight - 240 ) + 2 ) , Colors::Red , 10 , 1 );
			text.drawText( gfx , "Ark Annoyed" , Vec2( screenHalfWidth + 3 , ( screenHalfHeight - 240 ) + 3 ) , Colors::Red , 10 , 1 );
			text.drawText( gfx , "Ark Annoyed" , Vec2( screenHalfWidth , screenHalfHeight - 240 ) , Colors::White , 10 , 1 );

			boxEasy.draw( gfx , true );
			boxMedium.draw( gfx , true );
			boxHard.draw( gfx , true );
			boxCreate.draw( gfx , true );

			text.drawText( gfx , "SFX" , Vec2( screenQuarterWidth - soundBoxW - 25 , 570.0f ) , Colors::White , 2 , 1 );
			text.drawText( gfx , std::to_string( int( soundEffectVol * 100 ) ) , Vec2( screenQuarterWidth + soundBoxW + 10 , 570.0f - soundBoxH - soundBoxH ) , Colors::White , 2 );
			boxSfx.draw( gfx );
			boxSfxVol.draw( gfx );

			text.drawText( gfx , "MUSIC" , Vec2( screen3QuarterWidth - soundBoxW - 35 , 570.0f ) , Colors::White , 2 , 1 );
			text.drawText( gfx , std::to_string( int( musicVol * 100 ) ) , Vec2( screen3QuarterWidth + soundBoxW + 10 , 570.0f - soundBoxH - soundBoxH ) , Colors::White , 2 );
			boxMusic.draw( gfx );
			boxMusicVol.draw( gfx );


			for ( auto& brick : bricks )
			{
				brick.draw( gfx );
			}

			balls[ 0 ].draw( gfx );
			paddle.draw( gfx );
			break;
		}
		case GameState::GAME_ACTIVE:
		{
			wall.draw( gfx );

			for ( const Brick& brick : bricks )
			{
				brick.draw( gfx );
			}

			for ( PowerUp& power : powers )
			{
				power.draw( gfx );

				if ( power.getPower( ) == PowerUp::powers::bullet )
				{
					power.drawBullets( gfx );
				}
			}

			for ( int i = 0; i < blockBricksCurr; i++ )
			{
				blockBricks[ i ].draw( gfx );
			}

			if ( timerStart.getState( ) )
			{
				paddle.draw( gfx );
				for ( int i = 0; i < currBalls; i++ )
				{
					balls[ i ].draw( gfx );
				}
			}

			if ( !timerStart.getState( ) )
			{
				if ( !timerFlickerAnim.getState( ) )
					text.drawText( gfx , "Round " + std::to_string( currentLevel ) , Vec2( screenHalfWidth , 435.0f ) , Colors::White , 3 , 1 );

				text.drawText( gfx , "Ready" , Vec2( screenHalfWidth , 475.0f ) , Colors::White , 3 , 1 );
			}

			text.drawText( gfx , "Time" , Vec2( 23.0f , 5.0f ) , Colors::White , 2 );
			drawTimeFormat( time , Vec2( 45.0f , 30.0f ) , 2 );

			text.drawText( gfx , "Lives" , Vec2( screenThirdHeight , 12.0f ) , Colors::Red , 2 , 1 );
			text.drawText( gfx , std::to_string( lives ) , Vec2( screenThirdHeight , 32.0f ) , Colors::White , 2 , 1 );

			text.drawText( gfx , "Score" , Vec2( screen2ThirdWidth , 12.0f ) , Colors::Red , 2 , 1 );
			text.drawText( gfx , std::to_string( score ) , Vec2( screen2ThirdWidth , 32.0f ) , Colors::White , 2 , 1 );

			returnBoxGame.draw( gfx , true );
			break;
		}
		case GameState::GAME_SCORE:
		{
			menuWall.draw( gfx );

			returnBoxScore.draw( gfx , true );

			text.drawText( gfx , scoreText , Vec2( screenHalfWidth + 1 , ( screenHalfHeight - 240 ) + 1 ) , Colors::Red , 10 , 1 );
			text.drawText( gfx , scoreText , Vec2( screenHalfWidth + 2 , ( screenHalfHeight - 240 ) + 2 ) , Colors::Red , 10 , 1 );
			text.drawText( gfx , scoreText , Vec2( screenHalfWidth + 3 , ( screenHalfHeight - 240 ) + 3 ) , Colors::Red , 10 , 1 );

			text.drawText( gfx , scoreText , Vec2( screenHalfWidth , ( screenHalfHeight - 240 ) ) , Colors::White , 10 , 1 );


			for ( const Brick& brick : bricks )
			{
				brick.draw( gfx );
			}

			text.drawText( gfx , "Time" , Vec2( screenHalfWidth - 80 , screen2ThirdHeight - 205 ) , Colors::Red , 4 , 1 );

			if ( !scoreFlickerAnim )
			{
				text.drawText( gfx , std::to_string( scoreDraw ) , Vec2( screenHalfWidth + 60 , screen2ThirdHeight - 65 ) , Colors::White , 4 , 1 );
				drawTimeFormat( timeDraw , Vec2( screenHalfWidth + 60 , screen2ThirdHeight - 205 ) , 4 );
			}
			else
			{
				if ( !timerFlickerAnim.getState( ) )
				{
					drawTimeFormat( timeDraw , Vec2( screenHalfWidth + 60 , screen2ThirdHeight - 205 ) , 4 );
					text.drawText( gfx , std::to_string( scoreDraw ) , Vec2( screenHalfWidth + 60 , screen2ThirdHeight - 65 ) , Colors::White , 4 , 1 );
				}
			}

			text.drawText( gfx , "Score" , Vec2( screenHalfWidth - 75 , screen2ThirdHeight - 65 ) , Colors::Red , 4 , 1 );

			balls[ 0 ].draw( gfx );
			paddle.draw( gfx );

			break;
		}
		case GameState::GAME_CREATE:
		{
			break;
		}
	}
}
