#pragma once
#include "Candies.hpp"
#include "vector"
#include "stdlib.h"
#include "iostream"

class Grid
// acts as a wrapper for all the drawing and for the vectors
// all actions on the grid itself are done here
{
private:
    std::vector<std::vector<Candy *>> gameGrid;
    void swap(Point pos1, Point pos2);
    int caseType(Point pos1, int direction) const;
    void remove(Point pos);
    void fillEmpty();
    Candy *randomCandy(int x, int y);

public:
    Grid();
    ~Grid();
    void render() const;
    void refresh();
    Candy *grab(Point mouseLoc, Candy *grabbed);
    void ungrab(Point mouseLoc, Candy *grabbed);
    bool isAdjacent(Point pos1, Point pos2) const;
    bool isValidMove(Point pos1, Point pos2) const;
    void print();
};
