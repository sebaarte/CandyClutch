#pragma once
#include <Point.hpp>
#include "Animations.hpp"
#include "memory"
#define FL_PINK fl_rgb_color(255, 192, 203)
#define FL_BROWN fl_rgb_color(150, 75, 0)
#define FL_PURPLE fl_rgb_color(128, 0, 28)

class Candy
{
protected:
    Point _relativepos;
    Point _absolutepos;
    Point relativeToAbsolute();
    int _type;
    bool _grabbed = false;
    bool animated = false;
    std::unique_ptr<Animation> animation;
    Fl_Color color;

public:
    Candy(Point pos);
    Candy(int x, int y);
    Candy(Point pos, std::unique_ptr<Animation> anim);
    Candy(int x, int y, std::unique_ptr<Animation> anim);
    virtual void draw() = 0;
    bool contains(Point mouseLoc);
    const Point absolutePos() const;
    const Point relativePos() const;
    void grab(Point mouseLoc);
    void ungrab();
    void setPos(Point newPos);
    const int type() const;
    const bool grabbed() const { return _grabbed; }
    void translate();
    void refreshAnimation();
    bool animationOver(){return animation->isOver();}
    void suppress();
};

class Napoleone : public Candy
{
public:
    Napoleone(Point pos) : Candy(pos)
    {
        color = FL_YELLOW;
        _type = 1;
    }
    Napoleone(int x, int y) : Candy(x, y)
    {
        color = FL_YELLOW;
        _type = 1;
    }
    ~Napoleone() = default;
    void draw() override;
};

class Fruitello : public Candy
{
public:
    Fruitello(Point pos) : Candy(pos) { _type = 2; color = FL_PINK;}
    Fruitello(int x, int y) : Candy(x, y) { _type = 2; color = FL_PINK;}
    ~Fruitello() = default;
    void draw() override;
};

class Magnom : public Candy
{
public:
    Magnom(Point pos) : Candy(pos) { _type = 3; color = FL_BLACK;}
    Magnom(int x, int y) : Candy(x, y) { _type = 3; color = FL_BLACK;}
    ~Magnom() = default;
    void draw() override;
};

class Chocoteuf : public Candy
{
public:
    Chocoteuf(Point pos) : Candy(pos) { _type = 4; color = FL_BROWN;}
    Chocoteuf(int x, int y) : Candy(x, y) { _type = 4; color = FL_BROWN;}
    ~Chocoteuf() = default;
    void draw() override;
};

class Haribot : public Candy
{
public:
    Haribot(Point pos) : Candy(pos) { _type = 5; color = FL_PURPLE;}
    Haribot(int x, int y) : Candy(x, y) { _type = 5;color = FL_PURPLE; }
    ~Haribot() = default;
    void draw() override;
};

class Chique : public Candy
{
public:
    Chique(Point pos) : Candy(pos) { _type = 6; color = FL_BLUE;}
    Chique(int x, int y) : Candy(x, y) { _type = 6; color = FL_BLUE;}
    ~Chique() = default;
    void draw() override;
};

class Empty : public Candy
{
public:
    Empty(Point pos) : Candy(pos) { _type = -1; }
    Empty(int x, int y) : Candy(x, y) { _type = -1; }
    ~Empty() = default;
    void draw() override;
};
