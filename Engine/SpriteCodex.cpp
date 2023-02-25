#include "SpriteCodex.h"

void SpriteCodex::DrawBall( const Vec2& topLeft,Graphics& gfx )
{
	const int x = int( topLeft.x ) - 7;
	const int y = int( topLeft.y ) - 7;

	gfx.PutPixel(5 + x, 0 + y, 48, 48, 48);
	gfx.PutPixel(6 + x, 0 + y, 48, 48, 48);
	gfx.PutPixel(7 + x, 0 + y, 48, 48, 48);
	gfx.PutPixel(8 + x, 0 + y, 48, 48, 48);
	gfx.PutPixel(3 + x, 1 + y, 48, 48, 48);
	gfx.PutPixel(4 + x, 1 + y, 48, 48, 48);
	gfx.PutPixel(5 + x, 1 + y, 248, 224, 96);
	gfx.PutPixel(6 + x, 1 + y, 248, 200, 72);
	gfx.PutPixel(7 + x, 1 + y, 200, 168, 72);
	gfx.PutPixel(8 + x, 1 + y, 248, 200, 72);
	gfx.PutPixel(9 + x, 1 + y, 48, 48, 48);
	gfx.PutPixel(10 + x, 1 + y, 48, 48, 48);
	gfx.PutPixel(2 + x, 2 + y, 48, 48, 48);
	gfx.PutPixel(3 + x, 2 + y, 248, 224, 96);
	gfx.PutPixel(4 + x, 2 + y, 248, 224, 96);
	gfx.PutPixel(5 + x, 2 + y, 248, 224, 96);
	gfx.PutPixel(6 + x, 2 + y, 248, 224, 96);
	gfx.PutPixel(7 + x, 2 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 2 + y, 200, 168, 72);
	gfx.PutPixel(9 + x, 2 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 2 + y, 248, 200, 72);
	gfx.PutPixel(11 + x, 2 + y, 48, 48, 48);
	gfx.PutPixel(1 + x, 3 + y, 48, 48, 48);
	gfx.PutPixel(2 + x, 3 + y, 248, 224, 96);
	gfx.PutPixel(3 + x, 3 + y, 248, 224, 96);
	gfx.PutPixel(4 + x, 3 + y, 248, 248, 248);
	gfx.PutPixel(5 + x, 3 + y, 248, 248, 248);
	gfx.PutPixel(6 + x, 3 + y, 248, 224, 96);
	gfx.PutPixel(7 + x, 3 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 3 + y, 248, 200, 72);
	gfx.PutPixel(9 + x, 3 + y, 152, 112, 16);
	gfx.PutPixel(10 + x, 3 + y, 200, 168, 72);
	gfx.PutPixel(11 + x, 3 + y, 200, 168, 72);
	gfx.PutPixel(12 + x, 3 + y, 48, 48, 48);
	gfx.PutPixel(1 + x, 4 + y, 48, 48, 48);
	gfx.PutPixel(2 + x, 4 + y, 248, 224, 96);
	gfx.PutPixel(3 + x, 4 + y, 248, 224, 96);
	gfx.PutPixel(4 + x, 4 + y, 248, 248, 248);
	gfx.PutPixel(5 + x, 4 + y, 248, 248, 248);
	gfx.PutPixel(6 + x, 4 + y, 248, 224, 96);
	gfx.PutPixel(7 + x, 4 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 4 + y, 248, 200, 72);
	gfx.PutPixel(9 + x, 4 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 4 + y, 152, 112, 16);
	gfx.PutPixel(11 + x, 4 + y, 152, 112, 16);
	gfx.PutPixel(12 + x, 4 + y, 48, 48, 48);
	gfx.PutPixel(0 + x, 5 + y, 48, 48, 48);
	gfx.PutPixel(1 + x, 5 + y, 248, 200, 72);
	gfx.PutPixel(2 + x, 5 + y, 248, 224, 96);
	gfx.PutPixel(3 + x, 5 + y, 248, 224, 96);
	gfx.PutPixel(4 + x, 5 + y, 248, 224, 96);
	gfx.PutPixel(5 + x, 5 + y, 248, 224, 96);
	gfx.PutPixel(6 + x, 5 + y, 248, 224, 96);
	gfx.PutPixel(7 + x, 5 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 5 + y, 248, 200, 72);
	gfx.PutPixel(9 + x, 5 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 5 + y, 152, 112, 16);
	gfx.PutPixel(11 + x, 5 + y, 152, 112, 16);
	gfx.PutPixel(12 + x, 5 + y, 200, 168, 72);
	gfx.PutPixel(13 + x, 5 + y, 48, 48, 48);
	gfx.PutPixel(0 + x, 6 + y, 48, 48, 48);
	gfx.PutPixel(1 + x, 6 + y, 248, 200, 72);
	gfx.PutPixel(2 + x, 6 + y, 248, 200, 72);
	gfx.PutPixel(3 + x, 6 + y, 248, 224, 96);
	gfx.PutPixel(4 + x, 6 + y, 248, 224, 96);
	gfx.PutPixel(5 + x, 6 + y, 248, 224, 96);
	gfx.PutPixel(6 + x, 6 + y, 248, 200, 72);
	gfx.PutPixel(7 + x, 6 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 6 + y, 248, 200, 72);
	gfx.PutPixel(9 + x, 6 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 6 + y, 152, 112, 16);
	gfx.PutPixel(11 + x, 6 + y, 152, 112, 16);
	gfx.PutPixel(12 + x, 6 + y, 152, 112, 16);
	gfx.PutPixel(13 + x, 6 + y, 48, 48, 48);
	gfx.PutPixel(0 + x, 7 + y, 48, 48, 48);
	gfx.PutPixel(1 + x, 7 + y, 200, 168, 72);
	gfx.PutPixel(2 + x, 7 + y, 248, 200, 72);
	gfx.PutPixel(3 + x, 7 + y, 248, 200, 72);
	gfx.PutPixel(4 + x, 7 + y, 248, 200, 72);
	gfx.PutPixel(5 + x, 7 + y, 248, 200, 72);
	gfx.PutPixel(6 + x, 7 + y, 248, 248, 248);
	gfx.PutPixel(7 + x, 7 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 7 + y, 200, 168, 72);
	gfx.PutPixel(9 + x, 7 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 7 + y, 152, 112, 16);
	gfx.PutPixel(11 + x, 7 + y, 152, 112, 16);
	gfx.PutPixel(12 + x, 7 + y, 152, 112, 16);
	gfx.PutPixel(13 + x, 7 + y, 48, 48, 48);
	gfx.PutPixel(0 + x, 8 + y, 128, 88, 0);
	gfx.PutPixel(1 + x, 8 + y, 200, 168, 72);
	gfx.PutPixel(2 + x, 8 + y, 200, 168, 72);
	gfx.PutPixel(3 + x, 8 + y, 248, 200, 72);
	gfx.PutPixel(4 + x, 8 + y, 248, 200, 72);
	gfx.PutPixel(5 + x, 8 + y, 248, 200, 72);
	gfx.PutPixel(6 + x, 8 + y, 248, 200, 72);
	gfx.PutPixel(7 + x, 8 + y, 200, 168, 72);
	gfx.PutPixel(8 + x, 8 + y, 200, 168, 72);
	gfx.PutPixel(9 + x, 8 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 8 + y, 152, 112, 16);
	gfx.PutPixel(11 + x, 8 + y, 152, 112, 16);
	gfx.PutPixel(12 + x, 8 + y, 200, 168, 72);
	gfx.PutPixel(13 + x, 8 + y, 128, 88, 0);
	gfx.PutPixel(1 + x, 9 + y, 152, 112, 16);
	gfx.PutPixel(2 + x, 9 + y, 152, 112, 16);
	gfx.PutPixel(3 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(4 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(5 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(6 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(7 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(8 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(9 + x, 9 + y, 152, 112, 16);
	gfx.PutPixel(10 + x, 9 + y, 152, 112, 16);
	gfx.PutPixel(11 + x, 9 + y, 200, 168, 72);
	gfx.PutPixel(12 + x, 9 + y, 192, 152, 56);
	gfx.PutPixel(1 + x, 10 + y, 128, 88, 0);
	gfx.PutPixel(2 + x, 10 + y, 248, 200, 72);
	gfx.PutPixel(3 + x, 10 + y, 152, 112, 16);
	gfx.PutPixel(4 + x, 10 + y, 152, 112, 16);
	gfx.PutPixel(5 + x, 10 + y, 200, 168, 72);
	gfx.PutPixel(6 + x, 10 + y, 152, 112, 16);
	gfx.PutPixel(7 + x, 10 + y, 200, 168, 72);
	gfx.PutPixel(8 + x, 10 + y, 152, 112, 16);
	gfx.PutPixel(9 + x, 10 + y, 152, 112, 16);
	gfx.PutPixel(10 + x, 10 + y, 200, 168, 72);
	gfx.PutPixel(11 + x, 10 + y, 248, 200, 72);
	gfx.PutPixel(12 + x, 10 + y, 128, 88, 0);
	gfx.PutPixel(2 + x, 11 + y, 48, 48, 48);
	gfx.PutPixel(3 + x, 11 + y, 248, 200, 72);
	gfx.PutPixel(4 + x, 11 + y, 200, 168, 72);
	gfx.PutPixel(5 + x, 11 + y, 152, 112, 16);
	gfx.PutPixel(6 + x, 11 + y, 152, 112, 16);
	gfx.PutPixel(7 + x, 11 + y, 152, 112, 16);
	gfx.PutPixel(8 + x, 11 + y, 152, 112, 16);
	gfx.PutPixel(9 + x, 11 + y, 200, 168, 72);
	gfx.PutPixel(10 + x, 11 + y, 248, 200, 72);
	gfx.PutPixel(11 + x, 11 + y, 48, 48, 48);
	gfx.PutPixel(3 + x, 12 + y, 48, 48, 48);
	gfx.PutPixel(4 + x, 12 + y, 152, 112, 16);
	gfx.PutPixel(5 + x, 12 + y, 248, 200, 72);
	gfx.PutPixel(6 + x, 12 + y, 248, 200, 72);
	gfx.PutPixel(7 + x, 12 + y, 248, 200, 72);
	gfx.PutPixel(8 + x, 12 + y, 248, 200, 72);
	gfx.PutPixel(9 + x, 12 + y, 152, 112, 16);
	gfx.PutPixel(10 + x, 12 + y, 48, 48, 48);
	gfx.PutPixel(5 + x, 13 + y, 48, 48, 48);
	gfx.PutPixel(6 + x, 13 + y, 48, 48, 48);
	gfx.PutPixel(7 + x, 13 + y, 48, 48, 48);
	gfx.PutPixel(8 + x, 13 + y, 48, 48, 48);	
}

void SpriteCodex::DrawPaddle(const Vec2& center, Graphics& gfx, int add)
{
	const int x = int( center.x ) - int(PADDLE_HALF_WIDTH);
	const int xL = (int(center.x) - int(PADDLE_HALF_WIDTH) ) - add ;
	const int xR = (int( center.x ) + int(PADDLE_HALF_WIDTH) ) + add ;
	const int y = int(center.y) - 8;

	gfx.DrawRect( x + 20 , y, x + 80 , y + 16 , fill );

	gfx.DrawRect( xL + 20, y , xL + 50 , y + 16 , fill );
	gfx.DrawRect( xR - 50 , y , xR - 20 , y + 16 , fill );

	////right
	gfx.DrawRect( xR - 16 , y , xR - 10 , y + 16 , orange);
	gfx.DrawRect( xR - 10 , y + 1 , xR - 6 , y + 15 , orange );

	////left
	gfx.DrawRect( xL + 10 , y , xL + 16 , y + 16 , orange );
	gfx.DrawRect( xL + 6 , y + 1 , xL + 10 , y + 15 , orange );


	gfx.DrawRect( xL + 9, y + 3 , xR - 9 , y + 5 , Colors::MakeRGB( 215,215,215 ));

	////left
	gfx.DrawRect( xL + 16 , y , xL + 20 , y + 16 , Colors::Black );

	////right
	gfx.DrawRect( xR - 20 , y , xR - 16 , y + 16 , Colors::Black );
	
	 
	////left

	gfx.DrawRect( xL , y + 5, xL + 6 , y + 11 , outline );
	gfx.DrawRect( xL + 2, y + 2 , xL + 6 , y + 5 , outline );
	gfx.DrawRect( xL + 2 , y + 11 , xL + 6 , y + 14 , outline );

	gfx.DrawRect( xL + 1 , y + 6 , xL + 6 , y + 10 , blink );
	gfx.DrawRect( xL + 3 , y + 3 , xL + 6 , y + 6 , blink );
	gfx.DrawRect( xL + 3 , y + 10 , xL + 6 , y + 13 , blink );

	////right

	gfx.DrawRect( xR - 6, y + 5 , xR , y + 11 , outline );
	gfx.DrawRect( xR - 6 , y + 2 , xR - 2 , y + 5 ,	outline );
	gfx.DrawRect( xR - 6 , y + 11 , xR - 2 , y + 14 , outline );

	gfx.DrawRect( xR - 6, y + 6 , xR - 1 , y + 10 , blink );
	gfx.DrawRect( xR - 6 , y + 3 , xR - 3 , y + 6 , blink );
	gfx.DrawRect( xR - 6 , y + 10 , xR - 3 , y + 13 , blink );

	gfx.DrawRect( xL + 4 , y + 5 , xL + 9 , y + 7 , Colors::MakeRGB( 215 , 215 , 215 ) );
}

void SpriteCodex::DrawBullet( const Vec2& center , Graphics& gfx )
{
	const int x = int( center.x - 4.0f );
	const int y = int( center.y  - 8.0f );

	gfx.DrawRect( x , y + 3, x + 8 , y + 16 , Colors::Black );
	gfx.DrawRect( x + 2 , y + 5 , x + 6 , y + 14 , Colors::Yellow );

	gfx.DrawRect( x + 3, y  , x + 5 , y + 3 , Colors::White );

}

void SpriteCodex::DrawBulletDestroyed( const Vec2& center , Graphics& gfx)
{
	const int x = int( center.x - 4.0f );
	const int y = int( center.y - 8.0f );

	gfx.DrawRect( x + 3, y , x + 5 , y + 2 , Colors::White );
	gfx.DrawRect( x , y + 5, x + 2 , y + 7 , Colors::White );
	gfx.DrawRect( x+ 6 , y + 5 , x + 8 , y + 7 , Colors::White );
}
