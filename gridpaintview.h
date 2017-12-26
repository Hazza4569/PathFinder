#ifndef GRIDPAINTVIEW_H
#define GRIDPAINTVIEW_H

#include <QWidget>

#include "squaregrid.h"

class GridPaintView : public QWidget
{
    Q_OBJECT
public:
    GridPaintView(QWidget* parent = 0);

    void SetGrid(Grid *value) { fGrid = value; }

    void SetReset(bool value) { fReset = value; }
    bool GetReset() { return fReset; }

protected:
    void paintEvent(QPaintEvent *event) override; //QPainter * painter, const QRectF & rect);

private:
    Grid* fGrid;
    bool fReset;

};

#endif // GRIDPAINTVIEW_H
