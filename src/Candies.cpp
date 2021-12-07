#include "Candies.hpp"
#include "FL/fl_draw.H"
#include "constantes.hpp"

#define FL_PINK fl_rgb_color(255, 192, 203)
#define FL_BROWN fl_rgb_color(150, 75, 0)
#define FL_PURPLE fl_rgb_color(128, 0, 28)
/////////////////////////////////////////// candy methods
Candy::Candy(int x, int y)
{
    _relativepos = Point{x, y};
    _absolutepos = relativeToAbsolute();
}

bool Candy::contains(Point mouseLoc)
{
    const Point candyPos = absolutePos();
    if ((mouseLoc.x <= candyPos.x + candySize / 2) && (mouseLoc.x >= candyPos.x - candySize / 2) && (mouseLoc.y <= candyPos.y + candySize / 2) && (mouseLoc.y >= candyPos.y - candySize / 2))
    {
        return True;
    }
    return false;
}

Point Candy::relativeToAbsolute()
{
    return Point{offset + candySize / 2 + 10 + _relativepos.x * 90, offset + candySize / 2 + 10 + _relativepos.y * 90};
}

void Candy::ungrab()
{
    _absolutepos = relativeToAbsolute();
}

const Point Candy::absolutePos() const
{
    return static_cast<const Point>(_absolutepos);
}

const Point Candy::relativePos() const
{
    return static_cast<const Point>(_relativepos);
}

void Candy::grab(Point mouseLoc)
{
    _absolutepos = mouseLoc;
}

void Candy::setPos(Point newPos)
{
    _relativepos = newPos;
    _absolutepos = relativeToAbsolute();
}

/////////////// all draw methods overriden
void Napoleone::draw()
{
    fl_draw_box(FL_FLAT_BOX, _absolutepos.x - candySize / 2, _absolutepos.y - candySize / 2, candySize, candySize, FL_YELLOW);
}

void Fruitello::draw()
{
    fl_draw_box(FL_FLAT_BOX, _absolutepos.x - candySize / 2, _absolutepos.y - candySize / 2, candySize, candySize, FL_PINK);
}

void Magnom::draw()
{
    fl_draw_box(FL_FLAT_BOX, _absolutepos.x - candySize / 2, _absolutepos.y - candySize / 2, candySize, candySize, FL_BLACK);
}

void Chocoteuf::draw()
{
    fl_draw_box(FL_FLAT_BOX, _absolutepos.x - candySize / 2, _absolutepos.y - candySize / 2, candySize, candySize, FL_BROWN);
}

void Haribot::draw()
{
    fl_draw_box(FL_FLAT_BOX, _absolutepos.x - candySize / 2, _absolutepos.y - candySize / 2, candySize, candySize, FL_PURPLE);
}

void Chique::draw()
{
    fl_draw_box(FL_FLAT_BOX, _absolutepos.x - candySize / 2, _absolutepos.y - candySize / 2, candySize, candySize, FL_BLUE);
}

