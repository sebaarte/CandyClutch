#include "Grid.hpp"

Grid::Grid()
{
    //generates a 7x7 grid filled with random Candies
    for (int y = 0; y < 7; y++)
    {
        // Vector to store column elements
        std::vector<Candy *> v1;

        for (int x = 0; x < 7; x++)
        {
            int r = rand() % 6 + 1;
            switch (r)
            {
            case 1:
                v1.push_back(new Napoleone(x, y));
                break;
            case 2:
                v1.push_back(new Fruitello(x, y));
                break;
            case 3:
                v1.push_back(new Magnom(x, y));
                break;
            case 4:
                v1.push_back(new Chocoteuf(x, y));
                break;
            case 5:
                v1.push_back(new Haribot(x, y));
                break;
            case 6:
                v1.push_back(new Chique(x, y));
                break;
            }
        }
        gameGrid.push_back(v1);
    }
}

Grid::~Grid()
{
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            delete j;
        }
    }
}

void Grid::render()
{
    // displays different candies in the window
    for (unsigned long y = 0; y < 7; y++)
    {
        for (unsigned long x = 0; x < 7; x++)
        {
            gameGrid[y][x]->draw(Point{x,y});
        }
    }
}