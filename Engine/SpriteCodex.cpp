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

void SpriteCodex::DrawPaddle(const Vec2& center, Graphics& gfx)
{
	const int x = int(center.x) - 50;
	const int y = int(center.y) - 8;

	gfx.DrawRect(Rect(x, x + 100, y, y + 1), Colors::MakeRGB(200, 200, 200));

	gfx.DrawRect(Rect(x, x + 100, y + 1, y + 2), Colors::MakeRGB( 50, 50, 50));
	gfx.DrawRect(Rect(x + 2, x + 98, y + 2 , y + 5), Colors::MakeRGB(50, 50, 50) );
	gfx.DrawRect(Rect(x + 4, x + 96, y + 5, y + 8), Colors::MakeRGB(50, 50, 50));
	gfx.DrawRect(Rect(x + 6, x + 94, y + 8, y + 11), Colors::MakeRGB(50, 50, 50));
	gfx.DrawRect(Rect(x + 8, x + 92, y + 11, y + 14), Colors::MakeRGB(50, 50, 50));
	gfx.DrawRect(Rect(x + 10, x + 90, y + 14, y + 15), Colors::MakeRGB(50, 50, 50));

	gfx.PutPixel(x + 1, y + 1, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 2, y + 2, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 2, y + 3, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 3, y + 4, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 4, y + 5, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 4, y + 6, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 5, y + 7, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 6, y + 8, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 6, y + 9, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 7, y + 10, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 8, y + 11, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 8, y + 12, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 9, y + 13, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 10, y + 14,  Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 10, y + 15, Colors::MakeRGB(200, 200, 200));

	gfx.PutPixel(x + 100, y + 1, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 99, y + 1, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 98, y + 2, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 98, y + 3, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 97, y + 4, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 96, y + 5, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 96, y + 6, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 95, y + 7, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 94, y + 8, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 94, y + 9, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 93, y + 10, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 92, y + 11, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 92, y + 12, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 91, y + 13, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 90, y + 14, Colors::MakeRGB(200, 200, 200));
	gfx.PutPixel(x + 90, y + 15, Colors::MakeRGB(200, 200, 200));

	gfx.DrawRect(Rect(x + 10, x + 90, y + 15, y + 16), Colors::MakeRGB(200, 200, 200));
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
