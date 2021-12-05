#pragma once
#include "Candies.hpp"
#include "vector"
#include "stdlib.h"

class Grid
{
private:
    std::vector<std::vector<Candy>> gameGrid;

public:
    Grid();
    ~Grid();
};

Grid::Grid()
{
    //generates a 7x7 grid filled with random Candies
        for (int i = 0; i < 7; i++)
        {
            // Vector to store column elements
            std::vector<Candy> v1;

            for (int j = 0; j < 7; j++)
            {
                int r = rand() % 6 + 1;
                switch (r)
                {
                case 1:
                    v1.push_back(Napoleone(i,j));
                    break;
                case 2:
                    v1.push_back(Fruitello(i,j));
                    break;
                case 3:
                    v1.push_back(Magnom(i,j));
                    break;
                case 4:
                    v1.push_back(Chocoteuf(i,j));
                    break;
                case 5:
                    v1.push_back(Haribot(i,j));
                    break;
                case 6:
                    v1.push_back(Chique(i,j));
                    break;
                }
            }
            gameGrid.push_back(v1);
        }
    }

Grid::~Grid()
{
}
