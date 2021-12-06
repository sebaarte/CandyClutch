#include "PhysicsEngine.hpp"
#include "Fl/fl_draw.H"

PhysicsEngine::PhysicsEngine() : g{} {}

PhysicsEngine::~PhysicsEngine(){g.~Grid();}

void PhysicsEngine::draw()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            fl_draw_box(FL_FLAT_BOX,20+j*90,20+i*90,80,80,FL_WHITE);
            //printf("x: %d      y: %d\n",20+j*90,20+i*90);
        }
    }
    
    g.render();
}
void PhysicsEngine::mouseMove(Point mouseLoc)
{
}
void PhysicsEngine::mouseClick(Point mouseLoc)
{
}
void PhysicsEngine::keyPressed(int /*keyCode*/) { exit(0); }