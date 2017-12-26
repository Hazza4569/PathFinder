#ifndef HEXGRID_H
#define HEXGRID_H

#include "grid.h"

class HexGrid : public Grid
{
public:
    HexGrid(QWidget* parent);
    HexGrid(QWidget* parent, int width, int height);

    void FillNodes();
    void DefineNeighbours();

    void Draw(QPainter* painter, int visWidth, int visHeight);
};

#endif // HEXGRID_H
