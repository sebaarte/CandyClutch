#pragma once
#include "Candies.hpp"
#include "vector"
#include "Grid.hpp"



class PhysicsEngine{
// basically the link between front end (window) and back end (Grid)
    Grid g;
public:
    PhysicsEngine();
    ~PhysicsEngine();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int /*keyCode*/);
};