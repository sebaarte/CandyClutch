#pragma once
#include <Point.hpp>

class Candy
{
    Point _pos;

public:
    Candy(Point pos) : _pos(pos) {}
    Candy(int x, int y) { _pos = Point{x, y}; }
    virtual void draw() = 0;
    virtual void mouseMove(Point mouseLoc);
    virtual void mouseClick(Point mouseLoc);
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
