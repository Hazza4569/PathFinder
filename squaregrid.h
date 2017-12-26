#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include "grid.h"

class SquareGrid : public Grid
{
public:
    SquareGrid(QWidget* parent);
    SquareGrid(QWidget* parent, int width, int height);

    void FillNodes();
    void DefineNeighbours();

    void Draw(QPainter* painter, int visWidth, int visHeight);

};

#endif // SQUAREGRID_H
