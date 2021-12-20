#pragma once
#include <Point.hpp>

class Candy
{
protected:
    Point _relativepos;
    Point _absolutepos;
    Point relativeToAbsolute();
    int _type;
public:
    Candy(Point pos) : _relativepos(pos) {_absolutepos = relativeToAbsolute();}
    Candy(int x, int y);
    virtual void draw() const  = 0;
    bool contains(Point mouseLoc);
    const Point absolutePos() const;
    const Point relativePos() const;
    void grab(Point mouseLoc);
    void ungrab();
    void setPos(Point newPos);
    const int type() const;
};

class Napoleone : public Candy
{
public:
    Napoleone(Point pos) : Candy(pos) {_type = 1;}
    Napoleone(int x, int y): Candy(x, y){_type = 1;}
    ~Napoleone() = default;
    void draw() const override;
};

class Fruitello : public Candy
{
public:
    Fruitello(Point pos) : Candy(pos) {_type = 2;}
    Fruitello(int x, int y): Candy(x, y){_type = 2;}
    ~Fruitello() = default;
    void draw() const override;
};

class Magnom : public Candy
{
public:
    Magnom(Point pos) : Candy(pos) {_type = 3;}
    Magnom(int x, int y): Candy(x, y){_type = 3;}
    ~Magnom() = default;
    void draw() const override;
};

class Chocoteuf : public Candy
{
public:
    Chocoteuf(Point pos) : Candy(pos) {_type = 4;}
    Chocoteuf(int x, int y): Candy(x, y){_type = 4;}
    ~Chocoteuf() = default;
    void draw() const override;
};

class Haribot : public Candy
{
public:
    Haribot(Point pos) : Candy(pos) {_type = 5;}
    Haribot(int x, int y): Candy(x, y){_type = 5;}
    ~Haribot() = default;
    void draw() const override;
};

class Chique : public Candy
{
public:
    Chique(Point pos) : Candy(pos) {_type = 6;}
    Chique(int x, int y): Candy(x, y){_type = 6;}
    ~Chique() = default;
    void draw() const override;
};

class Empty: public Candy
{
public:
    Empty(Point pos) : Candy(pos) {_type = -1;}
    Empty(int x, int y): Candy(x, y){_type = -1;}
    ~Empty() = default;
    void draw() const override;
};



