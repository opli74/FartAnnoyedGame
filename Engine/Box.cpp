#include "Box.h"

Box::Box( const Rect& rec ,  const Color& border_c , const Color& fill_c , int border , bool fill )
	:
	rect( rec ),
	border( border_c ),
	fill( fill_c ),
	borderWidth( border ),
	typeFill(fill )
{
	center = Vec2( rect.left + ( rec.right - rect.left ) / 2 , rect.top + ( rect.bottom - rect.top ) / 2 );
	string = "";
}

Box::Box( const Rect& rec , const Color& border_c , const Color& fill_c , const Color& txtCol , const std::string& str , int size , int border )
	:
	textCol( txtCol ),
	textSize( size ),
	string( str ),
	rect( rec ) ,
	border( border_c ) ,
	fill( fill_c ) ,
	borderWidth( border )
{
	center = Vec2( rect.left + ( rec.right - rect.left ) / 2 , rect.top + ( rect.bottom - rect.top ) / 2 );

	typeFill = true;

	if ( !string.empty( ) )
		strEmpty = false;
}

Box::Box( const Rect& rec , const Color& c )
	:
	rect( rec ),
	fill( c )
{
	center = Vec2( rect.left + (rec.right - rect.left) / 2, rect.top + ( rect.bottom - rect.top) / 2);
	typeFill = true;
	borderWidth = 0;
	border = Color( NULL , NULL , NULL );
}

void Box::draw( Graphics& gfx , bool center_)
{
	if ( typeFill )
	{
		gfx.DrawRect( rect , fill );
		gfx.DrawRect( rect , border , borderWidth );
		text.drawText( gfx , string , center , textCol , textSize , center_ );
	}
	else
	{
		gfx.DrawRect( rect , border, borderWidth );
		text.drawText( gfx , string , center , textCol , textSize , center_ );
	}
}

void Box::draw( Graphics& gfx ) const
{
	if ( typeFill )
	{
		gfx.DrawRect( rect , fill );
	}
	else
	{
		gfx.DrawRect( rect , border );
	}
}

bool Box::isHover( Rect& rect )
{
	if ( getRect( ).isOverLapping( rect ) )
	{
		hover = true;
		return true;
	}
	hover = false;
	return false;
}

bool Box::isHover( Vec2& pos )
{
	if ( getRect( ).isOverLapping( pos ) )
	{
		hover = true;
		return true;
	}
	hover = false;
	return false;
}

bool Box::getIsHover( ) const
{
	return hover;
}

void Box::setTextCol( const Color& in )
{
	textCol = in;
}

void Box::setTextSize( int size )
{
	textSize = size;
}

void Box::setText( const std::string& in)
{
	if ( !in.empty( ) )
	{
		string = in;
		strEmpty = false;
	}
}

void Box::setFill( const Color& in )
{
	fill = in;
}

void Box::setBorder( const Color& in )
{
	border = in;
}

void Box::setBorderWidth( int in )
{
	borderWidth = in;
}

void Box::setRect( const Rect& in )
{
	rect = in;
}

void Box::setTypeFill( bool in )
{
	typeFill = in;
}

Rect Box::getRect( ) const
{
	return rect;
}
