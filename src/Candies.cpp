#include "Candies.hpp"
#include "FL/fl_draw.H"
#include "constantes.hpp"
#include "memory"

/////////////////////////////////////////// candy inherited methods
Candy::Candy(int x, int y)
{
    _relativepos = {x, y};
    _absolutepos = relativeToAbsolute(); 
}

Candy::Candy(int x, int y, std::unique_ptr<Animation> anim)
{
    _relativepos = {x, y};
    _absolutepos = relativeToAbsolute();
    animation = std::move(anim);
}

Candy::Candy(Point pos) : _absolutepos{pos}
{
    _absolutepos = relativeToAbsolute();
}

Candy::Candy(Point pos, std::unique_ptr<Animation> anim) : _relativepos{pos}
{
    _absolutepos = relativeToAbsolute();
    animation = std::move(anim);
}

bool Candy::contains(Point mouseLoc)
{
    const Point candyPos = absolutePos();
    if ((mouseLoc.x <= candyPos.x + CANDYSIZE / 2) && (mouseLoc.x >= candyPos.x - CANDYSIZE / 2) && (mouseLoc.y <= candyPos.y + CANDYSIZE / 2) && (mouseLoc.y >= candyPos.y - CANDYSIZE / 2))
    {
        return True;
    }
    return false;
}

Point Candy::relativeToAbsolute()
{
    return Point{OFFSET + CANDYSIZE / 2 + 10 + _relativepos.x * 90, OFFSET + CANDYSIZE / 2 + 10 + _relativepos.y * 90};
}

void Candy::grab()
{

    if (!animation->moving())
    {
        animation.release();
        animation = std::make_unique<Grabbed>(_absolutepos, color);
    }
}
void Candy::ungrab()
{
    std::cout << "ungrabbed candy at pos: " << _relativepos.x << " " << _relativepos.y << std::endl;
    animation.release();
    animation = std::make_unique<NoAnimation>(_absolutepos, color);
}

const Point Candy::absolutePos() const
{
    return static_cast<const Point>(_absolutepos);
}

const Point Candy::relativePos() const
{
    return static_cast<const Point>(_relativepos);
}

void Candy::setPos(Point newPos)
{
    _relativepos = newPos;
    _absolutepos = relativeToAbsolute();
}

const int Candy::type() const
{
    return _type;
}

void Candy::translate()
{
    _absolutepos = relativeToAbsolute();
    animation.release();
    animation = std::make_unique<Translation>(_absolutepos, color);
}

void Candy::refreshAnimation()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else
    {
        animation->refresh(_absolutepos);
    }
}

void Candy::suppress()
{
    if (!animation->moving())
    {
        animation.release();
        animation = std::make_unique<Suppression>(_absolutepos,color);
    }
    
}

bool Candy::animationOver()
{
    if (animation)
    {
        return animation->isOver();
    }
    return true;
}

void Candy::highlight()
{
    grab();
}
//////////////////////////////////////////////////// all draw methods overriden
void Napoleone::draw()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else if (animation->isOver())
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    
    animation->animate();
}

void Fruitello::draw()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else if (animation->isOver())
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    
    animation->animate();
}

void Magnom::draw()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else if (animation->isOver())
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    
    animation->animate();
}

void Chocoteuf::draw()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else if (animation->isOver())
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    
    animation->animate();
}

void Haribot::draw()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else if (animation->isOver())
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    
    animation->animate();
}

void Chique::draw()
{
    if (!animation)
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    else if (animation->isOver())
    {
        animation = std::make_unique<NoAnimation>(_absolutepos, color);
    }
    
    animation->animate();
}

void Empty::draw()
{
}
