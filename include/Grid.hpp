#pragma once
#include "Candies.hpp"
#include "vector"
#include "stdlib.h"

class Grid
// acts as a wrapper for all the drawing and for the vectors
// all actions on vectors and on the grid itself is done here
{
private:
    std::vector<std::vector<Candy*>> gameGrid;
    void swap(Point pos1, Point pos2);
    int neighboorType(Point pos1,int direction) const;
public:
    Grid();
    ~Grid();
    void render() const;
    Candy *grab(Point mouseLoc,Candy *grabbed);
    void ungrab(Point mouseLoc,Candy *grabbed);
    bool isAdjacent(Point pos1, Point pos2) const;
    bool isValidMove(Point pos1,Point pos2) const;
};
