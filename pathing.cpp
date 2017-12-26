#include "pathing.h"

#include <queue>

Pathing::Pathing()
{

}

void Pathing::Dijkstra(Grid* grid)
{
    std::vector<int> distanceTo(grid->GetSize(),INT_MAX-1);
    std::queue<int> q;

    int curr = grid->GetStart();
    distanceTo[curr] = 0;

    q.push(curr);

    while(!q.empty())
    {
        curr = q.front();
        std::vector<int> neighbours = grid->GetNode(curr)->GetNeighbourIDs();
        for (int i = 0; i < neighbours.size(); i++)
        {
            int iter = neighbours[i];
            if (distanceTo[iter] > distanceTo[curr]+1)
                    distanceTo[iter] = distanceTo[curr]+1;
            if (iter == grid->GetFinish(0)) break;
            q.push(iter);
        }
    }


}
