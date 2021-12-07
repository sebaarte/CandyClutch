#include "Grid.hpp"
#include "Fl/fl_draw.H"
#include "constantes.hpp"

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

void Grid::render() const
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            fl_draw_box(FL_FLAT_BOX, offset + j * 90, offset + i * 90, gridSize, gridSize, FL_WHITE);
        }
    }

    // displays different candies in the window
    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 7; x++)
        {
            gameGrid[y][x]->draw();
        }
    }
}

Candy *Grid::grab(Point mouseLoc)
{
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            if (j->contains(mouseLoc))
            {
                j->grab(mouseLoc);
                return j;
            }
        }
    }
    return nullptr;
}

void Grid::ungrab(Point mouseLoc, Candy *grabbed)
{
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            if (j->contains(mouseLoc))
            {
                swap(j->relativePos(), grabbed->relativePos());
            }
        }
    }
}

void Grid::swap(Point pos1, Point pos2)
{
    if (pos1 != pos2 && isAdjacent(pos1, pos2))
    {
        Candy *temp = gameGrid[pos1.y][pos1.x];
        gameGrid[pos1.y][pos1.x] = gameGrid[pos2.y][pos2.x];
        gameGrid[pos2.y][pos2.x] = temp;
        gameGrid[pos1.y][pos1.x]->setPos(pos2);
        gameGrid[pos2.y][pos2.x]->setPos(pos1);
    }
}

bool Grid::isAdjacent(Point pos1, Point pos2) const
{
    if ((pos1.x == pos2.x))
    {
        if (pos1.y+1 == pos2.y || pos1.y-1 == pos2.y)
        {
            return true;
        }
        
    }
    else if (pos1.x-1 == pos2.x || pos1.x+1 == pos2.x)
    {
        if (pos1.y == pos2.y)
        {
            return true;
        }
    }
    return false;
    
}