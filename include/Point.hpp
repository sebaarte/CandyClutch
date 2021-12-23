#pragma once
#include "iostream"
#include "constantes.hpp"

struct Point
{
    int x;
    int y;
    bool operator!=(const Point &other) const
    {
        return (x != other.x) || (y != other.y);
    }
    Point xAdd(int n) { return Point{x + n, y}; }
    Point yAdd(int n) { return Point{x, y + n}; }
    void print() { std::cout << x << " " << y << std::endl; }
    Point toAbsolute()
    {
        return Point{OFFSET + CANDYSIZE / 2 + 10 + x * 90, OFFSET + CANDYSIZE / 2 + 10 + y * 90};
    }
};
