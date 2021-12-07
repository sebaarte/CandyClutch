#pragma once
#include "Candies.hpp"
#include "vector"
#include "Grid.hpp"



class PhysicsEngine{
// basically the link between front end (window) and back end (Grid)
// mainly calls Grid
    Grid g;
    Candy *grabbed = nullptr;
public:
    PhysicsEngine();
    ~PhysicsEngine();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void drag(Point mouseLoc);
    void undrag(Point mouseLoc);
    void keyPressed(int /*keyCode*/);
};