#include "Grid.hpp"
#include "Fl/fl_draw.H"
#include "constantes.hpp"
#include "stdlib.h"
#include "Candies.hpp"

Grid::Grid()
{
    //generates a 7x7 grid filled with random Candies
    for (int y = 0; y < 7; y++)
    {
        // Vector to store column elements
        std::vector<Candy *> v1;

        for (int x = 0; x < 7; x++)
        {
            v1.push_back(randomCandy(x, y));
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
            fl_draw_box(FL_FLAT_BOX, offset + j * 90, offset + i * 90, squareSize, squareSize, FL_WHITE);
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

Candy *Grid::grab(Point mouseLoc, Candy *grabbed)
{
    if (!grabbed)
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
    else
    {
        grabbed->grab(mouseLoc);
        return grabbed;
    }
}

void Grid::ungrab(Point mouseLoc, Candy *grabbed)
{
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            if (j->contains(mouseLoc) && isAdjacent(j->relativePos(), grabbed->relativePos()) && isValidMove(j->relativePos(), grabbed->relativePos()))
            {
                swap(j->relativePos(), grabbed->relativePos());
                return;
            }
        }
    }
    grabbed->setPos(grabbed->relativePos());
}

void Grid::swap(Point pos1, Point pos2)
{
    gameGrid[pos1.y][pos1.x]->setPos(pos2);
    gameGrid[pos2.y][pos2.x]->setPos(pos1);
    std::iter_swap(gameGrid[pos1.y].begin() + pos1.x, gameGrid[pos2.y].begin() + pos2.x);
}

bool Grid::isAdjacent(Point pos1, Point pos2) const
{
    if ((pos1.x == pos2.x))
    {
        if (pos1.y + 1 == pos2.y || pos1.y - 1 == pos2.y)
        {
            return true;
        }
    }
    else if (pos1.x - 1 == pos2.x || pos1.x + 1 == pos2.x)
    {
        if (pos1.y == pos2.y)
        {
            return true;
        }
    }
    return false;
}

bool Grid::isValidMove(Point dest, Point source) const
{
    // big ugly function to check if the move creates a alignement of 3 Candies
    int destType = caseType(source, SELF);
    int sourceType = caseType(dest, SELF);
    bool sameType = (sourceType == destType);

    if (dest.x != source.x) // moving horizontally
    {
        if (caseType(dest, UP) == destType && (caseType(dest, DOUBLEUP) == destType || caseType(dest, DOWN) == destType))
        {
            return true;
        }
        if (caseType(source, UP) == sourceType && (caseType(source, DOUBLEUP) == sourceType || caseType(source, DOWN) == sourceType))
        {
            return true;
        }
        if (caseType(dest, DOWN) == destType && caseType(dest, DOUBLEDOWN) == destType)
        {
            return true;
        }
        if (caseType(source, DOWN) == sourceType && caseType(source, DOUBLEDOWN) == sourceType)
        {
            return true;
        }
        if (source.x < dest.x) // moving right
        {
            if (caseType(dest, RIGHT) == destType && (caseType(dest, DOUBLERIGHT) == destType || sameType))
            {
                return true;
            }
        }
        else // moving left
        {
            if (caseType(dest, LEFT) == sourceType && (caseType(dest, DOUBLELEFT) == sourceType || sameType))
            {
                return true;
            }
        }
    }
    else if (source.y != dest.y) // moving vertically
    {
        if (caseType(dest, LEFT) == destType && (caseType(dest, DOUBLELEFT) == destType || caseType(dest, RIGHT) == destType))
        {
            return true;
        }
        if (caseType(source, LEFT) == sourceType && (caseType(source, DOUBLELEFT) == sourceType || caseType(source, RIGHT) == sourceType))
        {
            return true;
        }
        if (caseType(dest, RIGHT) == destType && caseType(dest, DOUBLERIGHT) == destType)
        {
            return true;
        }
        if (caseType(source, RIGHT) == sourceType && caseType(source, DOUBLERIGHT) == sourceType)
        {
            return true;
        }
        if (source.y < dest.y) // moving up
        {
            if (caseType(dest, UP) == destType && (caseType(dest, DOUBLEUP) == destType || sameType))
            {
                return true;
            }
        }
        else // moving down
        {
            if (caseType(source, DOWN) == sourceType && (caseType(source, DOUBLEDOWN) == sourceType || sameType))
            {
                return true;
            }
        }
    }
    return false;
}

int Grid::caseType(Point pos, int direction) const
{
    switch (direction)
    {
    case UP:
        if (pos.y == 0)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y - 1][pos.x]->type();
        }
    case DOUBLEUP:
        if (pos.y < 2)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y - 2][pos.x]->type();
        }
    case DOWN:
        if (pos.y + 1 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y + 1][pos.x]->type();
        }
    case DOUBLEDOWN:
        if (pos.y + 1 == GRIDSIZE || pos.y + 2 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y + 2][pos.x]->type();
        }

    case LEFT:
        if (pos.x == 0)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x - 1]->type();
        }
    case DOUBLELEFT:
        if (pos.x < 2)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x - 2]->type();
        }
    case RIGHT:
        if (pos.x + 1 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x + 1]->type();
        }
        break;
    case DOUBLERIGHT:
        if (pos.x + 1 == GRIDSIZE || pos.x + 2 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x + 2]->type();
        }

    case SELF:
        return gameGrid[pos.y][pos.x]->type();
    default:
        return 0;
    }
}

void Grid::refresh()
{
    std::vector<Point> toClear = {};
    // clears line of same candies
    for (auto v : gameGrid)
    {
        for (auto j : v)
        {
            Point tempPos = j->relativePos();
            const int tempType = j->type();
            for (size_t i = 2; i < 4; i++)
            {
                if (caseType(tempPos, i) == j->type() && caseType(tempPos, i + 9) == j->type())
                {
                    if (i == 2)
                    {
                        toClear.push_back(tempPos);
                        toClear.push_back(tempPos.xAdd(1));
                        toClear.push_back(tempPos.xAdd(2));
                        for (size_t row = 3;; i++)
                        {
                            if (caseType(tempPos.xAdd(row), SELF) == tempType)
                            {
                                toClear.push_back(tempPos.xAdd(row));
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        toClear.push_back(tempPos);
                        toClear.push_back(tempPos.yAdd(1));
                        toClear.push_back(tempPos.yAdd(2));
                        for (size_t column = 3;; i++)
                        {
                            if (caseType(tempPos.yAdd(column), SELF) == tempType)
                            {
                                toClear.push_back(tempPos.yAdd(column));
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for (Point p : toClear)
    {
        remove(p);
    }
    fillEmpty();
}

void Grid::remove(Point p)
{
    gameGrid[p.y][p.x] = new Empty(p);
}

void Grid::fillEmpty()
{
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            if (j->type() == -1)
            {
                if (gameGrid[0][j->relativePos().x]->type() != -1)
                {
                    for (size_t row = 0; row < j->relativePos().y + 1; row++)
                    {
                        gameGrid[row][j->relativePos().x] = randomCandy(j->relativePos().y, row);
                    }
                }
                else
                {
                    Point start = j->relativePos();
                    
                }
            }
        }
    }
}

Candy *Grid::randomCandy(int x, int y)
{
    int r = rand() % 6 + 1;
    switch (r)
    {
    case 1:
        return new Napoleone(x,y);
    case 2:
        return new Fruitello(x,y);
    case 3:
        return new Magnom(x,y);
    case 4:
        return new Chocoteuf(x,y);
    case 5:
        return new Haribot(x,y);
    case 6:
        return new Chique(x,y);
    }
}