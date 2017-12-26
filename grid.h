#ifndef GRID_H
#define GRID_H

#include <vector>
#include <algorithm> //for std::remove()

#include <QGraphicsView>

#include "node.h"
#include "mainwindow.h"

class Grid
{
public:
    Grid(QWidget* parent);
    Grid(QWidget* parent, int width, int height);

    //Access methods
    int GetWidth() const { return fWidth; }
    void SetWidth(int value) { fWidth = value; }

    int GetHeight() const { return fHeight; }
    void SetHeight(int value) { fHeight = value; }

    void AddNode(Node* node) { fNodes.push_back(node); }
    Node* GetNode(int n) { return fNodes[n]; }
    Node* GetNode(QPoint p) { return GetNode(p.y()*fWidth + p.x()); }
    Node* GetNode(int x, int y) { return GetNode(y*fWidth + x); }

    QWidget* GetParent() { return fParent; }
    void SetParent(QWidget* value) { fParent = value; }

    int GetStart() { return fStart; }
    QPoint GetStartPoint();
    void SetStart(int value);
    void SetStart(QPoint p) { SetStart(p.y()*fWidth + p.x()); }
    void SetStart(int x, int y) { SetStart(y*fWidth + x); }
    void DeleteStart();

    int GetNFinish() { return fFinish.size(); }
    int GetFinish(int n) { return fFinish[n]; }
    QPoint GetFinishPoint(int n);
    void AddFinish(int value);
    void AddFinish(QPoint p) { AddFinish(p.y()*fWidth + p.x()); }
    void AddFinish(int x, int y) { AddFinish(y*fWidth + x); }
    void DeleteFinish(int value);
    void DeleteFinish(QPoint p) { DeleteFinish(p.y()*fWidth + p.x()); }
    void DeleteFinish(int x, int y) { DeleteFinish(y*fWidth + x); }
    void DeleteFinish() { DeleteFinish(GetFinish(GetNFinish()-1)); }

    int GetSize() { return fWidth*fHeight; }

    QBrush GetBrush(int x, int y);

    virtual void Draw(QPainter* painter, int visWidth, int visHeight) = 0;

    void Randomise(bool blocks, bool goal, bool start, int goals = 1, int density = 30);
                                //Density as percentage

private:
    QWidget* fParent;
    int fWidth, fHeight;
    std::vector<Node*> fNodes;
    int fStart;
    std::vector<int> fFinish;
};

#endif // GRID_H
