#include "node.h"

Node::Node()
    :fSolid(false), fGoal(false), fStart(false) {}

Node::Node(int id, bool isSolid, bool isGoal, bool isStart)
    : fSolid(isGoal || isStart ? false:isSolid), fGoal(isGoal), fStart(isStart), fIdentity(id) {}

void Node::SetIsSolid(bool value)
{
    fSolid = value;
    if (fSolid)
    {
        fGoal = false;
        fStart = false;
    }
}

void Node::SetIsGoal(bool value)
{
    fGoal = value;
    if (fGoal)
    {
        fSolid = false;
        fStart = false;
    }
}

void Node::SetIsStart(bool value)
{
    fStart = value;
    if (fStart)
    {
        fSolid = false;
        fGoal = false;
    }
}

std::vector<int> Node::GetNeighbourIDs()
{
    std::vector<int> IDs;
    std::vector<Node*> n = GetNeighbours();

    for (int i = 0; i < n.size(); i++)
        IDs.push_back(n[i]->Identify());

    return IDs;
}


void Node::Change(const Node& n)
{
    fSolid = n.fSolid;
    fGoal = n.fGoal;
}




