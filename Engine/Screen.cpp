#include "Screen.h"

void Screen::makeActive()
{
    active = true;
}

void Screen::endActive()
{
    active = false;
}

bool Screen::getActive()
{
    return active;
}
