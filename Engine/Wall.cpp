#include "Wall.h"

Wall::Wall(const Rect& rect, const Color& c)
    :
    rect(rect),
    c(c)
{
}

Rect Wall::getWall() const
{
    return Rect((rect.left + width), (rect.right - width), (rect.top + width), (rect.bottom - width));
}

void Wall::draw(Graphics& gfx) const
{
    gfx.DrawRect(int(rect.left), int(rect.bottom), int(rect.right), int(rect.bottom - width), c);
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.right), int(rect.top + width), c);
    gfx.DrawRect(int(rect.right), int(rect.top), int(rect.right - width), int(rect.bottom), c);
    gfx.DrawRect(int(rect.left), int(rect.top), int(rect.left + width), int(rect.bottom), c);
}
