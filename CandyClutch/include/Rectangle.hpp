#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <math.h>
#include "Point.hpp"

class Rectangle{
    int x_pos,y_pos,width, height;
    Fl_Color color;
    Fl_Color fcolor;
public:
    Rectangle(Point center,int w, int h, 
        Fl_Color frameColor=FL_BLACK, 
        Fl_Color fillColor=FL_WHITE);
    void draw();
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
};