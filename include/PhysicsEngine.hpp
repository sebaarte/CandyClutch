#pragma once
#include "Candies.hpp"
#include "vector"
#include "Grid.hpp"



class PhysicsEngine{
// basically an API to call the Grid.
// mainly calls Grid methods
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