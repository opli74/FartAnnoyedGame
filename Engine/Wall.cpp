#include "Wall.h"

Wall::Wall(const Rect& rect, const Color& c , bool type )
    :
    rect(rect),
    c(c),
    type( type )
{
    w = (rect.right - width) - (rect.left + width); 
    h = (rect.bottom - width) - (rect.top + width);

    cellW = w / float(cellX);
    cellH = h / float(cellY);

    topLeft = Vec2(rect.left + width, rect.top + width);
}

Wall::Wall( const Rect& rect , const Color& c , int x , int y , bool type )
    :
    rect( rect ) ,
    c( c ) ,
    type( type )

{
    cellX = x;
    cellY = y;

    w = ( rect.right - width ) - ( rect.left + width );
    h = ( rect.bottom - width ) - ( rect.top + width );

    cellW = w / float( cellX );
    cellH = h / float( cellY );

    topLeft = Vec2( rect.left + width , rect.top + width );
    
}

Rect Wall::getWall() const
{
    return Rect((rect.left + width), (rect.right - width), (rect.top + width), (rect.bottom - width));
}

void Wall::draw(Graphics& gfx) const
{
    if ( type )
        drawBorder(gfx);
    drawBackground(gfx);
}

void Wall::drawBorder(Graphics& gfx) const
{

    //right
    gfx.DrawRect(int(rect.right - width), int(rect.top), int(rect.right), int(rect.bottom), c);
    //right
    gfx.DrawRect(int(rect.right - width), int(rect.top + width), int(rect.right - width) + 2, int(rect.bottom - width) , borderD);

    //left
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.left + width), int(rect.bottom), c);
    //left
    gfx.DrawRect(int(rect.left + width), int(rect.top + width), int(rect.left + width) - 2, int(rect.bottom - width) , borderL);

    //bottom
    gfx.DrawRect(int(rect.left), int(rect.bottom - width), int(rect.right), int(rect.bottom), c);
    //bottom
    gfx.DrawRect(int(rect.left + width), int(rect.bottom - width), int(rect.right - width) + 2, int(rect.bottom - width) + 2, borderD);

    //top
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.right), int(rect.top + width), c);
    //top
    gfx.DrawRect(int(rect.left + width) - 2, int(rect.top + width), int(rect.right - width), int(rect.top + width) - 2, borderL);
    

    //bottom
    gfx.DrawRect(int(rect.left), int(rect.bottom - 2), int(rect.right), int(rect.bottom), borderD);
    //right
    gfx.DrawRect(int(rect.right), int(rect.top), int(rect.right - 2), int(rect.bottom), borderD);
    //left
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.left + 2), int(rect.bottom), borderL);
    //top
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.right), int(rect.top + 2), borderL);

}

void Wall::drawLines(Graphics& gfx) const
{
    for (int y = 0; y < cellY; y++)
    {
        for (int x = 0; x < cellX; x++)
        {
            if (y % 2 == 0)
            {
                if (x % 2 == 0)
                {
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), cellW, 1), l);
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), 1, cellH), d);
                }
            }
            else
            {
                if (x % 2 != 0)
                {
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), cellW , 1), l);
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), 1, cellH), d);
                }
            }
        }
    }
}

void Wall::drawBackground(Graphics& gfx) const
{
    for (int y = 0; y < cellY; y++)
    {
        for (int x = 0; x < cellX; x++)
        {
            if (y % 2 == 0)
                if (x % 2 == 0)
                {
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), cellW, cellH), greyOne);
                }

                else
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), cellW, cellH), greyTwo);
            else
                if (x % 2 != 0)
                {
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), cellW, cellH), greyOne);
                }

                else
                    gfx.DrawRect(Rect(topLeft + Vec2(float(x * cellW), float(y * cellH)), cellW, cellH), greyTwo);

        }
    }
    drawLines(gfx);
}
