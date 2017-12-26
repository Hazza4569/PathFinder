#ifndef PATHING_H
#define PATHING_H

#include "grid.h"

class Pathing
{
public:
    Pathing();

    void AStar(Grid* grid);
    void Dijkstra(Grid* grid);


};

#endif // PATHING_H
