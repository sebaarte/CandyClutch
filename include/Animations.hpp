#pragma once
#include "Point.hpp"
#include "FL/fl_draw.H"
#include "Fl/Fl.H"


class Animation
{
protected:
    unsigned counter;
    unsigned duration;
    Point _pos;
    Fl_Color _color;
public:
    Animation(Point absolutePos,Fl_Color color);
    ~Animation() = default;
    virtual void animate() = 0;
    bool isOver() {return counter == duration;}
    void refresh(Point pos);
    virtual bool moving() = 0;
};

class NoAnimation : public Animation
{
public:
    NoAnimation(Point absolutePos,Fl_Color color);
    ~NoAnimation() = default;
    void animate() override;
    bool moving() override {return false;}

};

class Translation: public Animation
{
public:
    Translation(Point absolutePos,Fl_Color color);
    ~Translation() = default;
    void animate() override;
    bool moving() override {return true;}
};

class Grabbed: public Animation
{
public:
    Grabbed(Point absolutePos,Fl_Color color);
    ~Grabbed() = default;
    void animate() override;
    bool moving() override {return true;}
};

class Suppression: public Animation
{
public:
    Suppression(Point absolutePos,Fl_Color color);
    ~Suppression() = default;
    void animate() override;
    bool moving() override {return true;}
};

class Slide: public Animation
{
    Point dest;
public:
    Slide(Point absolutePos,Fl_Color color,Point relativePos);
    ~Slide() = default;
    void animate() override;
    bool moving () override {return true;}
};