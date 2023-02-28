#include "Text.h"


void Text::drawText( Graphics& gfx, const std::string& text ,  Vec2 pos, int size)
{

	Vec2 pos_ = pos;
	std::vector<int> textToDraw;
	for ( char e : text )
	{
		textToDraw.push_back( int( e ) );
	}

	for ( int& e : textToDraw )
	{
		if ( (e > 96 && e < 122) || (e > 64 && e < 91) )
		{
			if ( e > 96 && e < 122 )
				e -= 32;

			drawLetter( e , size , gfx , pos_ , 65);

			pos_.x += ( size * textMap[ e - 65 ][ 0 ][ 0 ] + 2);
			
		}
		else if ( e > 47 && e < 59 )
		{
			drawLetter( e , size , gfx , pos_ , 22 );
			pos_.x += ( size * textMap[ e - 22 ][ 0 ][ 0 ] + 2 );
		}
		else if ( e == 46 )
		{
			drawLetter( e , size , gfx , pos_ , 9);
			pos_.x += ( size * textMap[ e - 22 ][ 0 ][ 0 ]  );
		}
		else
		{
			pos_.x += ( size * 5 );
		}
	}
}

void Text::drawLetter( int e , int size , Graphics& gfx, Vec2& pos, int f)
{
	int i = 0;
	for ( int y = 0; y < textMap[ e - f ][ 0 ][ 1 ]; y++ )
	{
		for ( int x = 0; x < textMap[ e - f ][ 0 ][ 0 ]; x++ )
		{
			if ( textMap[ e - f ][ 1 ][ i ] == 1 )
			{
				gfx.DrawRect( Rect( pos + Vec2( float(x * size) , float(y * size) ) , float(size) , float(size) ) , Colors::White );
			}
			i++;
		}
	}
}

