#include "Wall.h"

Wall::Wall(const Rect& rect, const Color& c)
    :
    rect(rect),
    c(c)
{
    w = (rect.right - width) - (rect.left + width); 
    h = (rect.bottom - width) - (rect.top + width);

    cellW = w / float(cellX);
    cellH = h / float(cellY);

    topLeft = Vec2(rect.left + width, rect.top + width);
}

Rect Wall::getWall() const
{
    return Rect((rect.left + width), (rect.right - width), (rect.top + width), (rect.bottom - width));
}

void Wall::draw(Graphics& gfx) const
{
    drawBorder(gfx);
    drawBackground(gfx);
}

void Wall::drawBorder(Graphics& gfx) const
{

    //right
    gfx.DrawRect(int(rect.right - width), int(rect.top), int(rect.right), int(rect.bottom), c);
    //right
    gfx.DrawRect(int(rect.right - width), int(rect.top + width), int(rect.right - width) + 2, int(rect.bottom - width) , d);

    //left
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.left + width), int(rect.bottom), c);
    //left
    gfx.DrawRect(int(rect.left + width), int(rect.top + width), int(rect.left + width) - 2, int(rect.bottom - width) , l);

    //bottom
    gfx.DrawRect(int(rect.left), int(rect.bottom - width), int(rect.right), int(rect.bottom), c);
    //bottom
    gfx.DrawRect(int(rect.left + width), int(rect.bottom - width), int(rect.right - width) + 2, int(rect.bottom - width) + 2, d);

    //top
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.right), int(rect.top + width), c);
    //top
    gfx.DrawRect(int(rect.left + width) - 2, int(rect.top + width), int(rect.right - width), int(rect.top + width) - 2, l);
    

    //bottom
    gfx.DrawRect(int(rect.left), int(rect.bottom - 2), int(rect.right), int(rect.bottom), d);
    //right
    gfx.DrawRect(int(rect.right), int(rect.top), int(rect.right - 2), int(rect.bottom), d);
    //left
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.left + 2), int(rect.bottom), l);
    //top
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.right), int(rect.top + 2), l);

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
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyOne);
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW) + 1, (y * cellH) + 1), cellW - 1, 1), d);
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW) + 1, (y * cellH) + 1), 1, cellH - 1), d);
                }

                else
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyTwo);
            else
                if (x % 2 != 0)
                {
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyOne);
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW) + 1, (y * cellH) + 1), cellW - 1, 1), d);
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW) + 1, (y * cellH) + 1), 1, cellH - 1), d);
                }

                else
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyTwo);

        }
    }
}
