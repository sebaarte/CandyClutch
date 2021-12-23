#include "Animations.hpp"
#include "cmath"
#include "constantes.hpp"
#include "Fl/Fl.H"
#include "Fl/fl_draw.H"

//////////////////////////////////////////////// animation constructors
Animation::Animation(Point pos, Fl_Color color) : _pos(pos), _color(color) { counter = 0; }

NoAnimation::NoAnimation(Point pos, Fl_Color color) : Animation(pos, color)
{
    duration = 1;
}

Translation::Translation(Point pos, Fl_Color color) : Animation(pos, color)
{
    duration = 60;
}

Grabbed::Grabbed(Point pos, Fl_Color color) : Animation(pos, color)
{
    duration = 121;
}

Suppression::Suppression(Point pos, Fl_Color color) : Animation(pos, color)
{
    duration = 30;

}
Slide::Slide(Point startpos,Fl_Color color,Point relativeDest) : Animation(startpos,color)
{
    dest = relativeDest.toAbsolute();
    

}

//////////////////////////// miscelanous Animation methods

void Animation::refresh(Point pos)
{
    _pos = pos;
}

/////////////////////////////////// different animations
void NoAnimation::animate()
{
    fl_draw_box(FL_FLAT_BOX, _pos.x - CANDYSIZE / 2, _pos.y - CANDYSIZE / 2, CANDYSIZE, CANDYSIZE, _color);
}

void Translation::animate()
{
    fl_draw_box(FL_FLAT_BOX, _pos.x - CANDYSIZE / 2, _pos.y - CANDYSIZE / 2 + (counter/2) - duration/2, CANDYSIZE, CANDYSIZE, _color);
    counter++;
}

void Grabbed::animate()
{

    if (counter <= duration / 2)
    {
        fl_draw_box(FL_FLAT_BOX, _pos.x - CANDYSIZE / 2, _pos.y - CANDYSIZE / 2, CANDYSIZE - counter / 6, CANDYSIZE - counter / 6, _color);
        counter++;
    }
    else if (counter == 120)
    {
        fl_draw_box(FL_FLAT_BOX, _pos.x - CANDYSIZE / 2, _pos.y - CANDYSIZE / 2, CANDYSIZE, CANDYSIZE, _color);
        counter = 0;
    }
    else if (counter > duration / 2)
    {
        fl_draw_box(FL_FLAT_BOX, _pos.x - CANDYSIZE / 2, _pos.y - CANDYSIZE / 2, CANDYSIZE - 10 + (counter - 60) / 6, CANDYSIZE - 10 + (counter - 60) / 6, _color);
        counter++;
    }
}

void Suppression::animate()
{
    fl_draw_box(FL_FLAT_BOX, _pos.x - CANDYSIZE / 2+(counter), _pos.y - CANDYSIZE / 2 + (counter), CANDYSIZE-(counter*2), CANDYSIZE- (counter*2), _color);
    counter++;
}

void Slide::animate()
{


}