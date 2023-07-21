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
	Box( const Rect& rec , const Color& fill_c , const Color& txtCol , const std::string& str , int size );
	Box( const Rect& rec ,  const Color& c ) ;

	//set
	void setTextCol( const Color& in );
	void setTextSize( int size );
	void setText( const std::string& in );

	void setBorder( const Color& in );
	void setFill( const Color& in );
	void setBorderWidth( int in );

	void setTypeFill( bool in );

	void setRect( const Rect& in );

	void setHovered( );

	//get
	void draw( Graphics& gfx ) const;
	void draw( Graphics& gfx , bool center );

	bool isHover( Rect& rect);
	bool isHover( Vec2& pos );

	bool checkHovered( );

	bool getIsHover( ) const;
	Rect getRect( ) const;

private:
	Text text;
	Color border , fill, textCol = Colors::White;
	Rect rect;
	Vec2 center;

	std::string string;

	int textSize = 4, borderWidth;

	bool hover , strEmpty = true, hovered = true, typeFill;
	
	

};

