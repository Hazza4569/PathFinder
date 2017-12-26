#ifndef GOAL_H
#define GOAL_H

#include<vector>

#include "point.h"
#include "grid.h"

class Goal: public Point {
public:
    Goal();
    Goal(Grid* grid, Point location);

    Grid GetGrid() const { return fGrid; }
    void SetGrid(const Grid &value) { fGrid = value; }

    Point GetLocation() const { return Point( X(), Y() ); }
    void SetLocation(const Point &value) { SetXY(value); }

    void Pather();
    void ClearMap();

    void PrintMap();

private:
    Grid fGrid;
    std::vector<std::vector<int> > fMap;
};

#endif // GOAL_H
