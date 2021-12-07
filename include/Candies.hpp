#pragma once
#include <Point.hpp>

class Candy
{
protected:
    Point _relativepos;
    Point _absolutepos;
    Point relativeToAbsolute();
public:
    Candy(Point pos) : _relativepos(pos) {_absolutepos = relativeToAbsolute();}
    Candy(int x, int y);
    virtual void draw() = 0;
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    bool contains(Point mouseLoc);
    const Point absolutePos() const;
    const Point relativePos() const;
    void grab(Point mouseLoc);
    void ungrab();
    void setPos(Point newPos);
};

class Napoleone : public Candy
{
public:
    Napoleone(Point pos) : Candy(pos) {}
    Napoleone(int x, int y): Candy(x, y){}
    ~Napoleone() = default;
    void draw() override;
};

class Fruitello : public Candy
{
public:
    Fruitello(Point pos) : Candy(pos) {}
    Fruitello(int x, int y): Candy(x, y){}
    ~Fruitello() = default;
    void draw() override;
};

class Magnom : public Candy
{
public:
    Magnom(Point pos) : Candy(pos) {}
    Magnom(int x, int y): Candy(x, y){}
    ~Magnom() = default;
    void draw() override;
};

class Chocoteuf : public Candy
{
public:
    Chocoteuf(Point pos) : Candy(pos) {}
    Chocoteuf(int x, int y): Candy(x, y){}
    ~Chocoteuf() = default;
    void draw() override;
};

class Haribot : public Candy
{
public:
    Haribot(Point pos) : Candy(pos) {}
    Haribot(int x, int y): Candy(x, y){}
    ~Haribot() = default;
    void draw() override;
};

class Chique : public Candy
{
public:
    Chique(Point pos) : Candy(pos) {}
    Chique(int x, int y): Candy(x, y){}
    ~Chique() = default;
    void draw() override;
};


