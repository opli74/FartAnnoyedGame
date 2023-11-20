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

	playSound( soundMusic , L"Sounds\\musicTitle.wav" , musicVol , 0.0f , 34.0f );

	levelChange( levels.loadTiles( GameLevel::Type::Menu , 1 ) , levels.getDimensions( GameLevel::Type::Menu , 1 ) );
}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = ft.Mark();

	// Calculate FPS
	fpsTimer += elapsedTime;
	frameCount++;

	if (fpsTimer >= 1.0f) // Update FPS every 1 second
	{
		fps = static_cast<float>(frameCount) / fpsTimer;
		fpsTimer = 0.0f;
		frameCount = 0;
	}

	while( elapsedTime > 0.0f )
	{
		const float dt = std::min(0.00025f, elapsedTime);
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

	switch ( state )
	{
		case GameState::GAME_MENU:
		{
			balls[ 0 ].anim( dt );
			paddle.setPos( Vec2( paddle.getVec( ).x + ( balls[ 0 ].getPosition( ).x - paddle.getVec( ).x ) / 400 * ( balls[ 0 ].getPosition( ).y / 400 ) , PADDLE_Y ) );
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

			for ( auto& [key, box] : menuBoxes )
			{
				playSoundOnce = true;
				if (box.isHover(mouse))
				{
					if (wnd.mouse.LeftIsPressed() && menuScreenWait.checkTime())
					{
						soundMusic.StopAll();
						playSound(soundChange, L"Sounds\\screenChange.wav", soundEffectVol);

						if ( key < (int)GameMenuOption::Create )
						{
							handleGameMenuSelection( (GameMenuOption)key, dt );
						}
						else
						{
							handleCreateMenuSelection();
						}
					}

					handleHoveredBox(box, (GameMenuOption)key);
				}
				else
				{
					handleUnhoveredBox(box, (GameMenuOption)key);
				}
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
					//soundMusic.StopAll( );
					//soundMusic.Play( 1.0f , musicVol );
					soundMusic.AdjustVolume( musicVol );
					soundMusicChange = false;
				}

				boxSfx.setFill( soundBoxCol );
				boxSfxVol.setFill( soundVolCol );

				boxSfxHoverActive = false;

				boxMusic.setFill( soundBoxCol );
				boxMusicVol.setFill( soundVolCol );
				boxMusicHoverActive = false;
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
					playSound( soundMusic , L"Sounds\\musicTitle.wav", musicVol, 0.0f, 34.0f );

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

					score = 0;
					lives = 6;
					time = 0;
				}

				if ( !returnHover )
				{
					playSound( soundPlay , L"Sounds\\button.wav" , soundEffectVol );
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

						playSound( soundChange , L"Sounds\\screenChange.wav" , soundEffectVol );

						if ( blockBricksCurr > 3 )
						{
							savedBlockBricks.erase( savedBlockBricks.begin( ) + 3 , savedBlockBricks.end( ) );
							blockBricksCurr = 3;
						}
						for ( const Brick& brick : savedBlockBricks )
						{
							bricks.push_back( brick );
						}
					}
					else
					{
						scoreText = "you win";
						currentLevel = 1;
						levelChange( levels.loadTiles( GameLevel::Type::Score , currentLevel ) , levels.getDimensions( GameLevel::Type::Score , currentLevel ) );
						savedBlockBricks.clear();
						state = GameState::GAME_SCORE;
					}

					pressed = true;
				}
			}
			else if ( wnd.kbd.KeyIsPressed( '3' ) )
			{
				if ( blockBricksCurr < 13 )
				{
					/*blockBricks[ blockBricksCurr ] = Brick( Rect( Vec2( blockBricksX + ( brickWidth * blockBricksCurr ) , blockBricksY ) , brickWidth , brickHeight ) , Colors::MakeRGB( 255 , 137 , 0 ) , 1 , Brick::Type::invinc );*/
					Brick blockBrick = Brick( Rect( Vec2( blockBricksX + ( brickWidth * blockBricksCurr ) , blockBricksY ) , brickWidth , brickHeight ) , 0, 0, Colors::MakeRGB( 255 , 137 , 0 ) , 99 , Brick::Type::invinc );
					bricks.push_back( blockBrick );
					savedBlockBricks.push_back( blockBrick );
					blockBricksCurr++;
				}
			}
			else if ( lives == 0 )
			{
				scoreText = "you lose";
				currentLevel = 1;
				levelChange( levels.loadTiles( GameLevel::Type::Score , currentLevel ) , levels.getDimensions( GameLevel::Type::Score , currentLevel ) );
				savedBlockBricks.clear( );
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
					score = 0;
					lives = 6;
					time = 0;
					play = true;

					playSound( soundMusic , L"Sounds\\musicTitle.wav" , musicVol , 0.0f , 34.0f );
					soundChange.StopAll( );

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
				for ( Brick& brick : bricks )
				{
					if ( brick.getType( ) == Brick::Type::extra ||
						 brick.getType( ) == Brick::Type::invinc )
					{
						brick.hit = true;
					}
				}
				brickAnim = false;
			}

			if ( timerStart.getState( ) )
			{

				if ( play )
				{
					soundMusic = Sound( L"Sounds\\music.wav" , 0.0f, 168.9f);
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

				int c = 0;
				for ( Brick& brick : bricks)
				{
					checkCollision( brick , c , collisionHappened , collisionDisSq , collisionIndex , ballIndex , dt );

					for ( PowerUp& power : powers )
					{
						if ( power.getPower( ) == PowerUp::powers::bullet )
						{
							for ( int f = 0; f < power.bullets.size( ); f++ )
							{
								if ( power.bullets[ f ].brickCollision( brick ) )
								{
									if ( ( brick.getType( ) == Brick::Type::extra ||
										   brick.getType( ) == Brick::Type::invinc ) && brick.health > 0 )
									{
										brick.hit = true;
									}
									if ( brick.getDestroyed( ) )
									{
										destroyed++;
										score += 10;
									}
								}
							}
						}
					}
					c++;
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
								break;
							}
							case Brick::Type::normal:
							{
								score += 20;
								break;
							}
						}

						if ( Random::getRand( 0 , powerFreq ) == powerFreq )
						{
							switch ( Random::getRand( 0 , 4 ) )
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
								case 3:
								{
									powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::block ) );
									break;
								}
								case 4:
								{
									powers.push_back( PowerUp( bricks[ collisionIndex ].getRect( ) , PowerUp::powers::bomb ) );
									break;
								}
							}
						}
						destroyed++;
					}

				}

				for ( int i = 0; i < currBalls; i++ )
				{
					if ( paddle.ballCollision( balls[ i ] ) )
					{
						playSound( soundPlay , L"Sounds\\arkpad.wav" , soundEffectVol );  
						break;
					}
				}

				for (size_t powerIndex = 0; powerIndex < powers.size(); powerIndex++)
				{
					PowerUp& power = powers[powerIndex];

					if ( spaceClicked )
						power.update( dt );

					if ( power.paddleCollision( paddle ) )
					{
						switch ( power.getPower( ) )
						{
							score += 80;
							case PowerUp::powers::length:
							{
								handleLengthPowerUp(paddle);
								break;
							}
							case PowerUp::powers::bullet:
							{
								handleBulletPowerUp(power, powerIndex);
								break;
							}
							case PowerUp::powers::balls:
							{
								handleBallsPowerUp();
								break;
							}
							case PowerUp::powers::block:
							{
								handleBlockPowerUp();
								break;
							}

							case PowerUp::powers::bomb:
							{
								handleBombPowerUp();
								break;
							}
						}
						powers.erase(powers.begin() + powerIndex);
						powerIndex--;
					}

					if ( power.getPower( ) == PowerUp::powers::bullet )
					{
						handleBulletPowerUpBehavior(power, dt);
					}

					if ( power.wallCollision( wall.getWall( ) ) )
					{
						powers.erase( powers.begin( ) + powerIndex);
						powerIndex--;
					}
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
			if ( !wnd.kbd.KeyIsEmpty( ) )
			{
				const Keyboard::Event event = wnd.kbd.ReadKey( );
				if ( event.IsPress( ) )
				{
					const unsigned char num_ = event.GetCode( );
					num = num_ - '0';
				}
				else if ( event.IsRelease( ) )
				{
					num = -1;
				}
			}

			for ( size_t i = 0 , e = bricks.size( ); i != e; i++ )
			{
				if ( bricks[ i ].isHover( mouse ) )
				{
					if ( num >= 0 && num <= 7 )
					{
						int x = bricks[ i ].getX( ) , y = bricks[ i ].getY( );
						Rect brickDim = Rect( topLeft + Vec2( x * brickWidth , y * brickHeight ) , brickWidth , brickHeight );

						switch ( num )
						{
							case 0:
							{
								if ( bricks[ i ].getType( ) == Brick::Type::empty ) { break; }

								bricks[ i ] = ( Brick( brickDim , x , y , Colors::MakeRGB( 60 , 60 , 60 ) , 1 , Brick::Type::empty ) );
								break;
							}
							case 1:
							case 2:
							case 3:
							case 4:
							case 5:
							{
								if( bricks[ i ].getColor( ) == brickColors[ num - 1 ] ) { break; }

								bricks[ i ] = ( Brick( brickDim , x , y , brickColors[ (num)-1 ] , 1 , Brick::Type::normal ) );
								break;
							}
							case 6:
							{
								if ( bricks[ i ].getType( ) == Brick::Type::invinc ) { break; }

								bricks[ i ] = ( Brick( brickDim , x , y , Colors::MakeRGB( 255 , 137 , 0 ) , 1 , Brick::Type::invinc ) );
								break;
							}
							case 7:
							{
								if ( bricks[ i ].getType( ) == Brick::Type::extra ) { break; }

								bricks[ i ] = ( Brick( brickDim , x , y , Colors::Gray , 2 , Brick::Type::extra ) );
								break;
							}
						}
					}
				}
			}
			break;
		}
	}
}

//GAME MENU
void Game::handleGameMenuSelection(GameMenuOption option, float dt)
{
	state = GameState::GAME_ACTIVE;
	levelChange(levels.loadTiles(GameLevel::Type::Game, currentLevel), levels.getDimensions(GameLevel::Type::Game, currentLevel));

	switch (option)
	{
	case GameMenuOption::Easy:
		configureGameParameters(5, 375.0f);
		break;
	case GameMenuOption::Medium:
		configureGameParameters(6, 465.0f);
		break;
	case GameMenuOption::Hard:
		configureGameParameters(8, 555.0f);
		break;
	default:
		break;
	}

	balls[0].update(dt);
	paddle.setSpeed();
}

void Game::handleCreateMenuSelection()
{
	state = GameState::GAME_CREATE;
	levelChange(levels.loadTiles(GameLevel::Type::Create, 4, true), levels.getDimensions(GameLevel::Type::Create, 4, true), true);
}

void Game::handleHoveredBox( Box& box, GameMenuOption option)
{
	if (box.checkHovered())
	{
		box.setFill(Colors::White);
		box.setBorder(Colors::Red);
		box.setTextCol(Colors::Black);

		if ((int)option < (int)GameMenuOption::Create)
		{
			box.setTextSize(5);
		}
		else
		{
			box.setTextSize(4);
		}

		playSound(soundPlay, L"Sounds\\button.wav", soundEffectVol);

		box.setHovered();
	}

}

void Game::handleUnhoveredBox(Box& box, GameMenuOption option)
{
	if (!box.checkHovered())
	{
		box.setHovered();

		if (option == GameMenuOption::Hard)
		{
			box.setFill(menuBoxCol);
			box.setBorder(Colors::White);
			box.setTextCol(Colors::Red);
			box.setTextSize(4);
			return;
		}

		box.setFill(menuBoxCol);
		box.setBorder(Colors::White);
		box.setTextCol(Colors::White);

		if (option < GameMenuOption::Create)
		{
			box.setTextSize(4);
		}
		else
		{
			box.setTextSize(3);
		}
	}
}

void Game::configureGameParameters(int frequency, float ballSpeed)
{
	powerFreq = frequency;
	G_BALL_SPEED = ballSpeed;
}


//GAME ACTIVE
void Game::handleLengthPowerUp(Paddle& paddle)
{
	playSound(soundPowerUp, L"Sounds\\arklengthen.wav", soundEffectVol);
	paddle.lengthPwrUp();
	offsetMaxMax = (paddle.getRect().right - paddle.getRect().left) / 2.0f - 15.0f;
	offsetMinMax = -offsetMaxMax;
}

void Game::handleBulletPowerUp(PowerUp& power, size_t powerIndex)
{
	playSound(soundPowerUp, L"Sounds\\arkbullet.wav", soundEffectVol);

	if (!hasBulletPower)
	{
		power.setCollisionWithPaddle(true);
		shotCount += 8;
		hasBulletPower = true;
	}
	else
	{
		power.setCollisionWithPaddle(true);
		shotCount += 8;
		// Assuming powers vector index 'i' is already known here
		powers.erase(powers.begin() + powerIndex);
	}
}

void Game::handleBallsPowerUp()
{
	playSound(soundPowerUp, L"Sounds\\arkpower.wav", soundEffectVol);
	int tempBalls = currBalls;
	currBalls *= 2;

	for (int i = 0; i < tempBalls; ++i)
	{
		for (int g = 0; g < 1; ++g)
		{
			float offsetX = getOffset(-100.0f, -275.0f, 100.0f, 275.0f);
			float offsetY = getOffset(-100.0f, -275.0f, 100.0f, 275.0f);
			balls.push_back(Ball(balls[i].getPosition(), Vec2(balls[i].getVelocity().x + offsetX, balls[i].getVelocity().y + offsetY)));
		}
	}
}

void Game::handleBlockPowerUp()
{
	playSound(soundPowerUp, L"Sounds\\arkpower.wav", soundEffectVol);

	if (blockBricksCurr < 14)
	{
		Brick blockBrick = Brick(Rect(Vec2(blockBricksX + (brickWidth * blockBricksCurr), blockBricksY), brickWidth, brickHeight),
			blockBricksCurr, 0, Colors::MakeRGB(255, 137, 0), 1, Brick::Type::invinc);
		bricks.push_back(blockBrick);
		savedBlockBricks.push_back(blockBrick);
		blockBricksCurr++;
	}
}

void Game::handleBombPowerUp()
{
	score -= 150;
	lives--;
}

void Game::handleBulletPowerUpBehavior(PowerUp& power, float dt )
{
	if (power.getCollisionWithPaddle())
	{
		if (!power.bulletExists() && shotCount == 0)
		{
			for ( size_t iter = 0, e = powers.size() - 1; iter != e; ++iter)
			{
				if (powers[iter].getPower() == PowerUp::powers::bullet && powers[iter].getCollisionWithPaddle())
				{
					powers[iter].bullets.clear();
					powers.erase(powers.begin() + iter);
				}
			}
			hasBulletPower = false;
		}
		else if (shotCount > 0)
		{
			if (power.shot(paddle, wnd.kbd, dt, spaceClicked))
			{
				playSound(soundPlay, L"Sounds\\arkbullet.wav", soundEffectVol);
				shotCount--;
			}
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



void Game::initializeLevel(const std::tuple<int, int>& dimensions)
{
	destroyed = 0;
	nonBrickAmount = 0;
	indestructable = 0;

	offsetMaxMax = 30.0f;
	offsetMinMax = -30.0f;

	hasBalls = false;

	std::tie(nBrickRows, nBrickCols) = dimensions;
	nBricks = nBrickCols * nBrickRows;

	offset = getOffset();

	brickAnim = true;

	timerStart.setState(false);
	timerStart.reset();
	spaceClicked = false;

	balls.erase(balls.begin() + 1, balls.end());
	currBalls = 1;
}

void Game::resetObjectsPositions()
{
	balls[0].setPosition(Vec2(400.0f + offset, PADDLE_Y - 12.0f));
	balls[0].setDirection(Vec2(0.0f, 5.0f));
	paddle.setPos(Vec2(400.0f, PADDLE_Y));
	paddle.lengthPwrUpReset();
}

void Game::initializeWallPadding()
{
	padX = ((wall.getWall().right - wall.getWall().left) - (nBrickRows * brickWidth)) / 2;
	padY = ((wall.getWall().bottom - wall.getWall().top) - (nBrickCols * brickHeight)) / 4;

	if (padY + (nBrickCols * brickHeight) > 340.0f)
	{
		padY -= ((nBrickCols * brickHeight) + padY) - 340.0f;
	}
	topLeft = Vec2((wall.getWall().left + padX), (wall.getWall().top + padY));
}

void Game::initializeBricks(const std::vector< int >& gameBricks, bool drawSpaceBricks)
{
	bricks.clear();
	for (PowerUp& e : powers)
	{
		e.bullets.clear();
	}
	powers.clear();
	hasBulletPower = false;

	for ( int y = 0; y < nBrickCols; y++)
	{
		for (int x = 0; x < nBrickRows; x++)
		{
			int brick = gameBricks[x + nBrickRows * y];

			switch (brick)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				{
					bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), x, y, brickColors[(brick)-1], 1, Brick::Type::normal));
					break;
				}
				case 6:
				{
					bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), x, y, Colors::MakeRGB(255, 137, 0), 1, Brick::Type::invinc));
					indestructable++;
					break;
				}
				case 7:
				{
					bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), x, y, Colors::Gray, 2, Brick::Type::extra));
					break;
				}
				default:
				{
					if (drawSpaceBricks)
					{
						bricks.push_back(Brick(Rect(topLeft + Vec2((x * brickWidth), (y * brickHeight)), brickWidth, brickHeight), x, y, Colors::MakeRGB(60, 60, 60), 1, Brick::Type::empty));
					}
					nonBrickAmount++;
					break;
				}
			}

		}
	}
}

void Game::levelChange( const std::vector< int >& gameBricks , const std::tuple<int , int>& dimensions , bool drawSpaceBricks )
{
	// Common initialization
	initializeLevel(dimensions);

	// Reset object positions
	resetObjectsPositions();

	// Initialize wall padding
	initializeWallPadding();

	// Create bricks
	initializeBricks(gameBricks, drawSpaceBricks);
}

//stops all sound and plays the file entered
void Game::playSound( Sound& sound , std::wstring file, float vol )
{
	sound.StopAll( );
	sound = Sound( file );
	sound.Play( 1.0f , vol );
}

//plays sound but loops it with start and end
void Game::playSound( Sound& sound , std::wstring file , float vol , float start , float end )
{
	sound.StopAll( );
	sound = Sound( file , start, end );
	sound.Play( 1.0f , vol);
}

//I used absoulte because the random libary kept throwing expceptions, here we just use a random num between 0 and 1 to see if the random should be negative or positive
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

std::string Game::removeTail(std::string& str)
{
	char decimalSeparator = '.';
	size_t index = str.find(decimalSeparator);

	if (index != std::string::npos)
	{
		// Found the decimal separator, remove the tail
		str.erase(str.begin() + index + 2, str.end());
	}

	return str;
}

//draws in-game timer with an actual timer layout, i.e: minutes:seconds:microseconds
void Game::drawTimeFormat( float time , Vec2 pos, int size )
{
	const int minutes = static_cast<int>(time / 60) % 60;
	const int seconds = static_cast<int>(time) % 60;
	const int milliseconds = static_cast<int>(time * 100) % 100;

	const std::string minutesStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
	const std::string secondsStr = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);
	const std::string millisecondsStr = (milliseconds < 10) ? "0" + std::to_string(milliseconds) : std::to_string(milliseconds);

	const std::string formattedTime = minutesStr + ":" + secondsStr + ":" + millisecondsStr;

	text.drawText(gfx, formattedTime, pos, Colors::White, size, true);
}

//checks collision for the passed brick, is used to ensure that only one brick is destroyed per frame
void Game::checkCollision( Brick& brick, int brickIndex, bool& collisionHappened , float& collisionDistSq , int& collisionIndex , int& ballIndex, float dt )
{
	brick.color( dt );
	const Vec2 brickCenter = brick.getRect().getCenter();
	for ( int b = 0; b < currBalls; b++ )
	{
		if ( brick.isCollidingBall( balls[ b ] ) )
		{
			const Vec2 ballPosition = balls[b].getPosition();
			const float newCollisionDistSq = (ballPosition - brickCenter ).GetLengthSq( );

			if (!collisionHappened || newCollisionDistSq < collisionDistSq)
			{
				collisionDistSq = newCollisionDistSq;
				collisionIndex = brickIndex;
				ballIndex = b;
				collisionHappened = true;

				// Early return if collision is found
				return;
			}
		}
	}
}

//various things to perfrom if collision happened
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

//draws the score with the flicker animation for the score screen. Uses a timer to flick between drawing and not drawing
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

void Game::drawTitle( )
{
	for ( int i = 1; i < 4; i++ )
	{
		text.drawText( gfx , "Ark Annoyed" , Vec2( screenHalfWidth + i , ( screenHalfHeight - 240 ) + i ) , Colors::Red , 10 , 1 );
	}
	text.drawText( gfx , "Ark Annoyed" , Vec2( screenHalfWidth , screenHalfHeight - 240 ) , Colors::White , 10 , 1 );
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
			
			drawTitle( );


			for ( auto& [key , box] : menuBoxes )
			{
				box.draw( gfx , true );
			}

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

			drawTitle( );


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

			for ( const Brick& brick : bricks )
			{
				brick.draw( gfx );
			}
			
			break;
		}
	}
	text.drawText(gfx, "fps: "+std::to_string(int(fps)) , Vec2(740, 5), Colors::White, 1);
}
