#pragma once
#include "Rectangle.hpp"



class Cell {
    Rectangle r;
public:
    Cell(Point center,int w, int h);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
};