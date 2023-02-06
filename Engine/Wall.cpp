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

    cBevel = Colors::MakeRGB(c.GetR(), c.GetG(), c.GetB() + 50);
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
    //bottom
    gfx.DrawRect(int(rect.left), int(rect.bottom - width / 2), int(rect.right), int(rect.bottom - width), c);
    gfx.DrawRect(int(rect.left), int(rect.bottom  - width / 2), int(rect.right), int(rect.bottom), cBevel);

    //top
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.right), int(rect.top + width / 2), cBevel);
    gfx.DrawRect(int(rect.left), int(rect.top + width / 2), int(rect.right), int(rect.top + width), c);
    //right
    gfx.DrawRect(int(rect.right), int(rect.top), int(rect.right - width / 2), int(rect.bottom), c);
    gfx.DrawRect(int(rect.right - width / 2), int(rect.top), int(rect.right - width), int(rect.bottom), cBevel);

    //left
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.left + width), int(rect.bottom), c);
}

void Wall::drawBackground(Graphics& gfx) const
{
    for (int y = 0; y < cellY; y++)
    {
        for (int x = 0; x < cellX; x++)
        {
            if (y % 2 == 0)
                if (x % 2 == 0)
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyOne);
                else
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyTwo);
            else
                if (x % 2 != 0)
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyOne);
                else
                    gfx.DrawRect(Rect(topLeft + Vec2((x * cellW), (y * cellH)), cellW, cellH), greyTwo);

        }
    }
}
