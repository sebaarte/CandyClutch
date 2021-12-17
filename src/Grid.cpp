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
    // printf("source %d, dest %d\n",sourceType,destType);
    // printf("source right %d, dest right %d\n",caseType(source,RIGHT),caseType(dest,RIGHT));
    // printf("source dright %d, dest dright %d\n",caseType(source,DOUBLERIGHT),caseType(dest,DOUBLERIGHT));
    printf("source left %d, dest left %d\n",caseType(source,LEFT),caseType(dest,LEFT));
    printf("source dleft %d, dest dleft %d\n",caseType(source,DOUBLELEFT),caseType(dest,DOUBLELEFT));
    // printf("source up %d, dest up %d\n",caseType(source,UP),caseType(dest,UP));
    // printf("source dup %d, dest dup %d\n",caseType(source,DOUBLEUP),caseType(dest,DOUBLEUP));
    // printf("source down %d, dest down %d\n",caseType(source,DOWN),caseType(dest,DOWN));
    // printf("source ddown %d, dest ddown %d\n",caseType(source,DOUBLEDOWN),caseType(dest,DOUBLEDOWN));



    if (dest.x != source.x) // moving horizontally
    {
        if (caseType(dest, UP) == destType && (caseType(dest, DOUBLEUP) == destType || caseType(dest, DOWN) == destType))
        {
            printf("memes cases verticales pour dest\n");
            return true;
        }
        if (caseType(source, UP) == sourceType && (caseType(source, DOUBLEUP) == sourceType || caseType(source, DOWN) == sourceType))
        {
            printf("memes cases verticales pour source\n");
            return true;
        }
        if (caseType(dest, DOWN) == destType && caseType(dest, DOUBLEDOWN) == destType)
        {
            printf("memes cases vers le bas pour dest\n");
            return true;
        }
        if (caseType(source, DOWN) == sourceType && caseType(source, DOUBLEDOWN) == sourceType)
        {
            printf("memes cases vers le bas pour source\n");
            return true;
        }
        if (source.x < dest.x) // moving right
        {
            if (caseType(dest, RIGHT) == destType && (caseType(dest, DOUBLERIGHT) == destType || sameType))
            {
                printf("memes cases horizontales pour dest\n");
                return true;
            }
        }
        else // moving left
        {
            if (caseType(dest, LEFT) == sourceType && (caseType(dest, DOUBLELEFT) == sourceType|| sameType))
            {
                printf("memes cases horizontales pour source\n");
                return true;
            }
        }
    }
    else if (source.y != dest.y) // moving vertically
    {
        if (caseType(dest, LEFT) == destType && (caseType(dest, DOUBLELEFT) == destType || caseType(dest, RIGHT) == destType))
        {
            printf("memes cases horizontales pour dest\n");
            return true;
        }
        if (caseType(source, LEFT) == sourceType && (caseType(source, DOUBLELEFT) == sourceType || caseType(source, RIGHT) == sourceType))
        {
            printf("memes cases horizontales pour source\n");
            return true;
        }
        if (caseType(dest, RIGHT) == destType && caseType(dest, DOUBLERIGHT) == destType)
        {
            printf("memes cases droites pour dest\n");
            return true;
        }
        if (caseType(source, RIGHT) == sourceType && caseType(source, DOUBLERIGHT) == sourceType)
        {
            printf("memes cases droites pour sources\n");
            return true;
        }
        if (source.y < dest.y) // moving up
        {
            if (caseType(dest, UP) == destType && (caseType(dest, DOUBLEUP) == destType || sameType))
            {
                printf("memes cases verticales pour dest\n");
                return true;
            }
        }
        else // moving down
        {
            if (caseType(source, DOWN) == sourceType && (caseType(source, DOUBLEDOWN) == sourceType || sameType))
            {
                printf("memes cases verticales pour source\n");
                return true;
            }
        }
    }
    printf("non\n");
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
            return gameGrid[pos.y - 1][pos.x]->type;
        }
    case DOUBLEUP:
        if (pos.y < 2)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y - 2][pos.x]->type;
        }
    case DOWN:
        if (pos.y + 1 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y + 1][pos.x]->type;
        }
    case DOUBLEDOWN:
        if (pos.y + 1 == GRIDSIZE || pos.y + 2 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y + 2][pos.x]->type;
        }

    case LEFT:
        if (pos.x == 0)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x - 1]->type;
        }
    case DOUBLELEFT:
        if (pos.x < 2)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x - 2]->type;
        }
    case RIGHT:
        if (pos.x + 1 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x + 1]->type;
        }
        break;
    case DOUBLERIGHT:
        if (pos.x + 1 == GRIDSIZE || pos.x + 2 == GRIDSIZE)
        {
            return 0;
        }
        else
        {
            return gameGrid[pos.y][pos.x + 2]->type;
        }

    case SELF:
        return gameGrid[pos.y][pos.x]->type;
    default:
        return 0;
    }
}