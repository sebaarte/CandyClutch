#pragma once
#include <Point.hpp>

class Candy
{
protected:
    Point _relativepos;
    Point _absolutepos;
    Point relativeToAbsolute();
public:
    int type;
    Candy(Point pos) : _relativepos(pos) {_absolutepos = relativeToAbsolute();}
    Candy(int x, int y);
    virtual void draw() const  = 0;
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
    Napoleone(Point pos) : Candy(pos) {type = 1;}
    Napoleone(int x, int y): Candy(x, y){type = 1;}
    ~Napoleone() = default;
    void draw() const override;
};

class Fruitello : public Candy
{
public:
    Fruitello(Point pos) : Candy(pos) {type = 2;}
    Fruitello(int x, int y): Candy(x, y){type = 2;}
    ~Fruitello() = default;
    void draw() const override;
};

class Magnom : public Candy
{
public:
    Magnom(Point pos) : Candy(pos) {type = 3;}
    Magnom(int x, int y): Candy(x, y){type = 3;}
    ~Magnom() = default;
    void draw() const override;
};

class Chocoteuf : public Candy
{
public:
    Chocoteuf(Point pos) : Candy(pos) {type = 4;}
    Chocoteuf(int x, int y): Candy(x, y){type = 4;}
    ~Chocoteuf() = default;
    void draw() const override;
};

class Haribot : public Candy
{
public:
    Haribot(Point pos) : Candy(pos) {type = 5;}
    Haribot(int x, int y): Candy(x, y){type = 5;}
    ~Haribot() = default;
    void draw() const override;
};

class Chique : public Candy
{
public:
    Chique(Point pos) : Candy(pos) {type = 6;}
    Chique(int x, int y): Candy(x, y){type = 6;}
    ~Chique() = default;
    void draw() const override;
};

class Empty: public Candy
{
public:
    Empty(Point pos) : Candy(pos) {}
    Empty(int x, int y): Candy(x, y){}
    ~Empty() = default;
    void draw() const override;
};



