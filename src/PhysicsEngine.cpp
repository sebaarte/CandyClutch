#include "PhysicsEngine.hpp"
#include "Fl/fl_draw.H"
#include "constantes.hpp"

PhysicsEngine::PhysicsEngine() : g{} {}

PhysicsEngine::~PhysicsEngine(){g.~Grid();}

void PhysicsEngine::draw()
{
    g.render();
}
void PhysicsEngine::mouseMove(Point mouseLoc)
{
}
void PhysicsEngine::mouseClick(Point mouseLoc)
{
}
void PhysicsEngine::keyPressed(int /*keyCode*/) { exit(0); }

void PhysicsEngine::drag(Point mouseLoc){
    grabbed = g.grab(mouseLoc);
}

void PhysicsEngine::undrag(Point mouseLoc)
{
    g.ungrab(mouseLoc,grabbed);
    grabbed = nullptr;
}