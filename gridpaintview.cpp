#include "gridpaintview.h"

#include <QDebug>

GridPaintView::GridPaintView(QWidget *parent)
    : QWidget(parent), fGrid(new SquareGrid(this)), fReset(false) {}

void GridPaintView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    qDebug() << fReset;

    if (fReset)
    {
        fReset = false;
        return;
    }

    painter.setPen(QColor(230,230,230));
    //painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
   // painter.drawRect(QRect(0, 0,width() - 1,height() - 1));

    fGrid->Draw(&painter, width(), height());

    //painter.setPen(QColor(180,180,180));
    //painter.setBrush(Qt::NoBrush);
    //painter.drawRect(QRect(0, 0,width() - 1,height() - 1));
}
