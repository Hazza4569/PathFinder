#ifndef NODE_H
#define NODE_H

#include <vector>

#include "point.h"

class Node {
public:
    Node();
    Node(int id, bool isSolid = false, bool isGoal = false, bool isStart = false);

    bool IsSolid() const { return fSolid; }
    void SetIsSolid(bool value = true);

    bool IsGoal() const { return fGoal; }
    void SetIsGoal(bool value = true);

    bool IsStart() const { return fStart; }
    void SetIsStart(bool value = true);

    int Identify() const { return fIdentity; }

    void AddNeighbour(Node* n) { fNeighbours.push_back(n); }
    std::vector<Node*> GetNeighbours() { return fNeighbours; }
    Node* GetNeighbour(int n) { return fNeighbours[n]; }
    int GetNNeighbours() { return fNeighbours.size(); }

    std::vector<int> GetNeighbourIDs();

    void Change(const Node& b);
    //currently unnecessary, but allows
    //flexibility for future implementation

private:
    int fIdentity;
    bool fSolid;
    bool fGoal;
    bool fStart;
    std::vector<Node*> fNeighbours;
};

#endif // NODE_H
//Node class not entirely necessary at this stage,
//could have a vector of points in grid class.
//Having the class gives the potential to add properties
//to the Nodes later on; may have different effects on
//the path finding.
