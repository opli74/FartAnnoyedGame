#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const Vec2& center,Graphics& gfx );
	static void DrawPaddle(const Vec2& center, Graphics& gfx, int add);
	static void DrawBullet( const Vec2& center , Graphics& gfx );
	static void DrawBulletDestroyed( const Vec2& center , Graphics& gfx );

private:
	static constexpr Color orange = Colors::MakeRGB( 255 , 125 , 0 );
	static constexpr Color outline = Colors::White;
	static constexpr Color fill = Colors::Gray;
	static constexpr Color blink = Colors::Red;
};