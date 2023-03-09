#pragma once
#include "Text.h"
#include "Rect.h"
#include "Graphics.h"
#include "Colors.h"
#include <string.h>

class Box
{
public:

	Box( ) = default;
	Box( const Rect& rec , const Color& border_c , const Color& fill_c ,int border , bool fill );
	Box( const Rect& rec , const Color& border_c , const Color& fill_c , const Color& txtCol, const std::string& str, int size, int border);
	Box( const Rect& rec ,  const Color& c ) ;

	void draw( Graphics& gfx ) const;
	void draw( Graphics& gfx , bool center );

	bool isHover( Rect& rect);
	bool isHover( Vec2& pos );

	void setTextCol( const Color& in );
	void setTextSize( int size );
	void setText( const std::string& in);

	void setBorder( const Color& in );
	void setFill( const Color& in );
	void setBorderWidth( int in );

	void setTypeFill( bool in );

	void setRect( const Rect& in );

	bool getIsHover( ) const;
	Rect getRect( ) const;

private:
	int textSize = 4;
	Color textCol = Colors::White;
	std::string string;
	Vec2 center;
	bool hover , strEmpty = true;
	Color border , fill;
	Rect rect;
	int borderWidth;
	bool typeFill;
	Text text;

};

