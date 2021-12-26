#include "Grid.hpp"
#include "Fl/fl_draw.H"
#include "constantes.hpp"
#include "stdlib.h"
#include "Candies.hpp"
#include "iostream"
#include "memory"
#include <FL/Fl_Text_Display.H>

Grid::Grid()
{
    //generates a 9x9 grid filled with random Candies
    for (int y = 0; y < GRIDSIZE; y++)
    {
        // Vector to store column elements
        std::vector<Candy *> v1;

        for (int x = 0; x < GRIDSIZE; x++)
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

void Grid::displayStartingScreen()
{
    fl_font(5, 50);
    fl_draw("Candy Clutch", WINDOWSIZE / 2, WINDOWSIZE / 2, WINDOWSIZE / 2, WINDOWSIZE / 2, FL_ALIGN_CENTER, nullptr, 1);
    fl_draw("Sébastien Arte", 0, 4 * WINDOWSIZE / 5);
}

void Grid::render(Candy *grabbed)
{
    // draws the empty squares behind the candies
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            fl_draw_box(FL_FLAT_BOX, OFFSET + j * 90, OFFSET + i * 90, SQUARESIZE, SQUARESIZE, FL_WHITE);
        }
    }
    // highlighting if the player takes too much time
    giveClue();

    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
                j->draw();
        }
    }
}

void Grid::giveClue()
{
    if (helpTimer == HELPTIME && !highlighted)
    {
        for (int i = 0; i < GRIDSIZE; i++)
        {
            for (int j = 0; j < GRIDSIZE; j++)
            {
                if (isValidMove({j + 1, i}, {j, i}) || isValidMove({j, i + 1}, {j, i}))
                {
                    int r = rand() % 5 + 1;
                    if (r == 1)
                    {
                        gameGrid.at(i).at(j)->highlight();
                        highlighted = new Point{j, i};
                        helpTimer = 0;
                        return;
                    }
                }
            }
        }
    }
    else
    {
        helpTimer = helpTimer % HELPTIME;
        helpTimer++;
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
                if (j->contains(mouseLoc) && j->type() != -1)
                {
                    j->grab();
                    return j;
                }
            }
        }
        return nullptr;
    }
    else
    {
        grabbed->grab();
        return grabbed;
    }
}

void Grid::ungrab(Point mouseLoc, Candy *grabbed)
{
    if (highlighted)
    {
        gameGrid.at(highlighted->y).at(highlighted->x)->ungrab();
        highlighted = nullptr;
    }
    helpTimer = 0;
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            if (j->type() != -1 && j->contains(mouseLoc) && isAdjacent(j->relativePos(), grabbed->relativePos()) && isValidMove(j->relativePos(), grabbed->relativePos()))
            {
                
                grabbed->slide(j->relativePos(),j->colour());
                j->slide(grabbed->relativePos(),grabbed->colour());
                swap(j->relativePos(), grabbed->relativePos());
                return;
            }
        }
    }
    grabbed->ungrab();
}

void Grid::swap(Point pos1, Point pos2)
{
    gameGrid.at(pos1.y).at(pos1.x)->setPos(pos2);
    
    gameGrid.at(pos2.y).at(pos2.x)->setPos(pos1);
    gameGrid.at(pos1.y).at(pos1.x)->refreshAnimation();
    gameGrid.at(pos2.y).at(pos2.x)->refreshAnimation();
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
    // big ugly function to check if the move creates an alignement of 3 Candies
    int destType = caseType(source, SELF);
    int sourceType = caseType(dest, SELF);
    bool sameType = (sourceType == destType);
    if (dest.y >= GRIDSIZE || dest.y <= -1 || dest.x >= GRIDSIZE || dest.x <= -1)
    {
        return false;
    }

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
            if (caseType(dest, LEFT) == destType && (caseType(dest, DOUBLELEFT) == destType || sameType))
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
        if (source.y > dest.y) // moving up
        {
            if (caseType(dest, UP) == destType && (caseType(dest, DOUBLEUP) == destType || sameType))
            {
                return true;
            }
            if (caseType(source, DOWN) == sourceType && (caseType(source, DOUBLEDOWN) == sourceType || sameType))
            {
                return true;
            }
        }
        else // moving down
        {
            if (caseType(source, UP) == sourceType && (caseType(source, DOUBLEUP) == sourceType || sameType))
            {
                return true;
            }
            if (caseType(dest, DOWN) == destType && (caseType(dest, DOUBLEDOWN) == destType || sameType))
            {
                return true;
            }
        }
    }
    return false;
}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int Grid::caseType(Point pos, int direction) const
{
    try
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
                return gameGrid.at(pos.y - 1).at(pos.x)->type();
            }
        case DOUBLEUP:
            if (pos.y < 2)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y - 2).at(pos.x)->type();
            }
        case DOWN:
            if (pos.y + 1 == GRIDSIZE)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y + 1).at(pos.x)->type();
            }
        case DOUBLEDOWN:
            if (pos.y >= GRIDSIZE - 2)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y + 2).at(pos.x)->type();
            }

        case LEFT:
            if (pos.x == 0)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y).at(pos.x - 1)->type();
            }
        case DOUBLELEFT:
            if (pos.x < 2)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y).at(pos.x - 2)->type();
            }
        case RIGHT:
            if (pos.x + 1 == GRIDSIZE)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y).at(pos.x + 1)->type();
            }
            break;
        case DOUBLERIGHT:
            if (pos.x >= GRIDSIZE - 2)
            {
                return 0;
            }
            else
            {
                return gameGrid.at(pos.y).at(pos.x + 2)->type();
            }

        case SELF:
            if (pos.x >= GRIDSIZE || pos.x <= -1 || pos.y >= GRIDSIZE || pos.y <= -1)
            {
                return 0;
            }
            return gameGrid.at(pos.y).at(pos.x)->type();
        default:
            return 0;
        }
    }
    catch (const std::out_of_range &e)
    {
        pos.print();
        std::cout << direction << "\n";
        std::cerr << e.what() << '\n';
    }
}

void Grid::refresh()
{
    std::vector<Point> toClear;
    // clears line of same candies
    for (auto v : gameGrid)
    {
        for (auto j : v)
        {
            if (j->type() != -1)
            {
                Point tempPos = j->relativePos();
                const int tempType = j->type();
                for (size_t i = 2; i < 4; i++)
                {
                    if (caseType(tempPos, i) == tempType && caseType(tempPos, i + 9) == tempType)
                    {
                        if (i == 2)
                        {

                            toClear.push_back(tempPos);
                            toClear.push_back(tempPos.xAdd(1));
                            toClear.push_back(tempPos.xAdd(2));
                            for (size_t row = 3; row < GRIDSIZE; row++)
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
                            for (size_t col = 3; col < GRIDSIZE; col++)
                            {
                                if (caseType(tempPos.yAdd(col), SELF) == tempType)
                                {
                                    toClear.push_back(tempPos.yAdd(col));
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
    }
    for (Point p : toClear)
    {
        std::cout << p.x << " " << p.y << std::endl;
        remove(p);
    }
    fillEmpty();
}

void Grid::remove(Point p)
{
    if (gameGrid.at(p.y).at(p.x)->animationOver() )
    {
        gameGrid.at(p.y).at(p.x) = new Empty(p);
        score += 10;
    }
    else
    {
        gameGrid.at(p.y).at(p.x)->suppress();
    }
}

void Grid::fillEmpty()
{

    for (int i = GRIDSIZE - 1; i > -1; i--) // for each y starting from the bottom
    {
        for (int j = 0; j < GRIDSIZE; j++) // for each x starting from left
        {
            if (gameGrid.at(i).at(j)->type() == -1) // if the case is empty
            {
                int start = i;
                for (int row = i; row > -1; row--) // going up from the case
                {
                    if (row == 0 && gameGrid.at(0).at(j)->type() == -1) // if all cases up to the top are empty
                    {
                        for (int k = i; k > -1; k--) // fill the empty column with random candies
                        {

                            gameGrid.at(k).at(j) = randomCandy(j, k);
                            gameGrid.at(k).at(j)->translate();
                        }
                        return;
                    }
                    else if (gameGrid.at(row).at(j)->type() != -1) // there's a candy somewhere above the empty case
                    {
                        swap({j, start}, {j, row});
                        break;
                    }
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
        return new Napoleone(x, y);
    case 2:
        return new Fruitello(x, y);
    case 3:
        return new Magnom(x, y);
    case 4:
        return new Chocoteuf(x, y);
    case 5:
        return new Haribot(x, y);
    case 6:
        return new Chique(x, y);
    }
}
#pragma GCC diagnostic pop

void Grid::print()
{
    for (auto i : gameGrid)
    {
        for (auto j : i)
        {
            std::cout << j->type() << " ";
        }
        std::cout << "\n";
    }
}