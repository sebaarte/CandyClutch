#pragma once

struct Point
{
    int x;
    int y;
    bool operator!=(const Point &other) const
    {
        return (x != other.x) || (y != other.y);
    }
    Point xAdd(int n){return Point{x+n,y};}
    Point yAdd(int n){return Point{x,y+n};}
};

