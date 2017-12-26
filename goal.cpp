#include <queue>
#include <iostream>

#include "goal.h"
#include "point.h"

Goal::Goal()
    : fGrid(Grid()) { SetXY(Point()); Pather(); }

Goal::Goal(Grid* grid, Point location)
    : fGrid(*grid) { SetXY(location); Pather(); }


void Goal::Pather()
{
    ClearMap();
    //rogue value - larger than any possible distance
    int rogue = fGrid.GetHeight()*fGrid.GetWidth()+1;

    //initialise map to rogue value for all empty grid
    //locations and -1 for all solid ones
    for (int i=0; i<=fGrid.GetWidth()+1; i++)
    {
        fMap.push_back(std::vector<int>());
        for (int j=0; j<=fGrid.GetHeight()+1; j++)
        {
            if (fGrid.GetNode(i,j)->IsSolid())
                fMap[i].push_back(-1);
            else
                fMap[i].push_back(rogue);
        }
    }

    //0 ditance to goal at goal:
    fMap[X()][Y()] = 0;

    //queue for points which need to be iterated over
    std::queue<Point> q;
    q.push(GetLocation());

    while(!q.empty())
    {
        Point p = q.front();
        int activeX(p.X()), activeY(p.Y());
        int activeDist = fMap[activeX][activeY];
        int relCoords[8] = {-1,0,0,1,0,-1,1,0};

        for (int i = 0; i<4; i++)
        {
            //find point to evaluate:
            int iterX = activeX+relCoords[2*i];
            int iterY = activeY+relCoords[2*i+1];

            //Get existing distance estimate to point
            int iterDist = fMap[iterX][iterY];

            //If
            if (iterDist > (activeDist+1))
            {
                fMap[iterX][iterY] = activeDist+1;
                q.push(Point(iterX,iterY));
            }
        }

        q.pop();
    }
}



void Goal::ClearMap()
{
    for(int i = 0; i<fMap.size(); i++) fMap[i].clear();
    fMap.clear();
}



void Goal::PrintMap()
{
    int X = fMap.size();
    int Y = fMap[0].size();
    for (int j = 0; j<Y; j++)
    {
        for (int i = 0; i<X; i++)
        {
            printf("%-5d", fMap[i][j]);
        }
        printf("\n");
    }
}
