#pragma once
#include "Cell.hpp"




class PhysicsEngine{
    Cell c;
public:
    PhysicsEngine():c{Point{250,250},100,100}{}; 
    void draw() {
        c.draw();
    }
    void mouseMove(Point mouseLoc) {
        c.mouseMove(mouseLoc);
    }
    void mouseClick(Point mouseLoc){
        c.mouseClick(mouseLoc);        
    }
    void keyPressed(int /*keyCode*/) {exit(0);}
};