#include <cstdlib>
#include <QDebug>

#include "grid.h"

Grid::Grid(QWidget* parent)
    : fParent(parent), fWidth(0), fHeight(0),
      fStart(-1),
      fFinish(std::vector<int>(1,-1))
    {}

Grid::Grid(QWidget* parent, int width, int height)
    : fParent(parent), fWidth(width), fHeight(height),
      fStart(-1),
      fFinish(std::vector<int>(1,-1))
{}

QPoint Grid::GetStartPoint()
{
    return QPoint(fStart%fWidth,trunc(fStart/fWidth));
}

void Grid::SetStart(int value)
{
    if (fStart >= 0 && fStart < fWidth*fHeight)
        GetNode(fStart)->SetIsGoal(false);
        //remove old start node if within grid

    if (value >= 0 && value < fWidth*fHeight)
    {
        //check if new start is already a finish, delete finish;
        for (int i = 0; i < GetNFinish(); i++)
        {
            if (value == GetFinish(i)) DeleteFinish(value);
        }
        //Set to start
        fStart = value;
        GetNode(fStart)->SetIsStart();
    }
    else
    {
        DeleteStart();
    }
}

void Grid::DeleteStart()
{
    if (fStart >= 0 && fStart < fWidth*fHeight)
        GetNode(fStart)->SetIsGoal(false);
        //remove old start node if within grid

    fStart = -1;
}

QPoint Grid::GetFinishPoint(int n)
{
    int f = GetFinish(n);
    return QPoint(f%fWidth,trunc(f/fWidth));
}

void Grid::AddFinish(int value)
{
    if (value >= 0 && value < fWidth*fHeight)
    {
        //replace start if necessary
        if (value == fStart) DeleteStart();

        //check if finish already exists
        bool flag = false;
        for (int i = 0; i < GetNFinish(); i++)
            if (value == GetFinish(i)) flag = true;
        if (!flag) fFinish.push_back(value);

        //Modufy node accordingly
        GetNode(value)->SetIsGoal();
    }
}

void Grid::DeleteFinish(int value)
{
    //Check value exists within fFinish vector
    bool flag = false;
    for (int i = 0; i < GetNFinish(); i++)
        if (GetFinish(i) == value) flag = true;

    //if it does, get rid of it
    if (flag)
    {
        GetNode(value)->SetIsGoal(false);
        if (GetNFinish() > 1) fFinish.erase(
            std::remove(fFinish.begin(),fFinish.end(),value),
            fFinish.begin()
        );
        //removes element == value, and reorders remaining elements
        else if (GetNFinish() == 1)
            fFinish[0] = -1;
    }
}

void Grid::Randomise(bool blocks, bool goal, bool start, int goals, int density)
{
    if (!(blocks || goal || start)) return;

    double blockChance = blocks ? density/100. : 0;
    int numGoals = goal ? goals : 0;

    if (start) SetStart(fWidth*fHeight*rand()/RAND_MAX);

    for (int i = 0; i < numGoals; i++)
    {
        int p;
        while (true)
        {
            p = fWidth*fHeight*rand()/RAND_MAX;
            if (!(GetNode(p)->IsGoal() || GetNode(p)->IsStart())) break;
        }
        AddFinish(p);
    }

    for (int i= 0; i < fWidth*fHeight; i++)
    {
        Node* n = GetNode(i);
        if (!(n->IsGoal() || n->IsStart()))
            if (double(rand())/RAND_MAX < blockChance)
                n->SetIsSolid();
    }
}

QBrush Grid::GetBrush(int x, int y)
{
    if (GetNode(GetWidth()*y + x)->IsSolid())
        return QBrush(QColor(120,120,120), Qt::SolidPattern);
    else if (GetNode(GetWidth()*y + x)->IsGoal())
        return QBrush(Qt::green, Qt::SolidPattern);
    else if (GetNode(GetWidth()*y + x)->IsStart())
        return QBrush(Qt::red, Qt::SolidPattern);
    else
        return QBrush(Qt::white, Qt::SolidPattern);
}
