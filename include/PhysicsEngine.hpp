#pragma once
#include "Candies.hpp"
#include "vector"
#include "Grid.hpp"



class PhysicsEngine{
// basically an API to call the Grid.
// mainly calls Grid methods
    Grid g;
    Candy *grabbed = nullptr;
    bool started = false;
public:
    PhysicsEngine();
    ~PhysicsEngine();
    void refresh();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void drag(Point mouseLoc);
    void undrag(Point mouseLoc);
    void keyPressed(int /*keyCode*/);
};