#pragma once
#include "Candies.hpp"
#include "vector"
#include "stdlib.h"

class Grid
// wrapper for the vector class
{
private:
    std::vector<std::vector<Candy*>> gameGrid;

public:
    Grid();
    ~Grid();
    void render();
};
