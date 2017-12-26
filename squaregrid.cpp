#include "squaregrid.h"

#include <QDebug>

SquareGrid::SquareGrid(QWidget* parent)
    : Grid(parent) {}

SquareGrid::SquareGrid(QWidget* parent, int width, int height)
    : Grid(parent, width, height)
{
    FillNodes();
    DefineNeighbours();
}

void SquareGrid::FillNodes()
{
    //Add nodes
    int nNodes = GetWidth()*GetHeight();

    for (int i = 0; i < nNodes; i++)
        AddNode(new Node(i));
}

void SquareGrid::DefineNeighbours()
{
    int width(GetWidth()), height(GetHeight());
    int active;

    //top-left corner:
    active = 0;
    GetNode(active)->AddNeighbour(GetNode(active+1));     //to the right
    GetNode(active)->AddNeighbour(GetNode(active+width)); //below

    //top row:
    for (int i = 1; i < (width-1); i++)
    {
        //(active = i)
        GetNode(i)->AddNeighbour(GetNode(i-1)); //to the left
        GetNode(i)->AddNeighbour(GetNode(i+1)); //to the right
        GetNode(i)->AddNeighbour(GetNode(i+width)); //below
    }

    //top-right corner
    active = width-1;
    GetNode(active)->AddNeighbour(GetNode(active-1));     //to the left
    GetNode(active)->AddNeighbour(GetNode(active+width)); //below

    //left column
    for (int j = 1; j < (height-1); j++)
    {
        active = j*width;
        GetNode(active)->AddNeighbour(GetNode(active-width)); //above
        GetNode(active)->AddNeighbour(GetNode(active+1));     //to the right
        GetNode(active)->AddNeighbour(GetNode(active+width)); //below
    }

    //central nodes:
    for (int i = 1; i < (width-1); i++)
    for (int j = 1; j < (height-1); j++)
    {
        active = j*width + i;
        GetNode(active)->AddNeighbour(GetNode(active-1));     //to the left
        GetNode(active)->AddNeighbour(GetNode(active-width)); //above
        GetNode(active)->AddNeighbour(GetNode(active+1));     //to the right
        GetNode(active)->AddNeighbour(GetNode(active+width)); //below
    }

    //right column
    for (int j = 1; j < (height-1); j++)
    {
        active = (j+1)*width - 1;
        GetNode(active)->AddNeighbour(GetNode(active-width)); //above
        GetNode(active)->AddNeighbour(GetNode(active-1));     //to the left
        GetNode(active)->AddNeighbour(GetNode(active+width)); //below
    }

    //bottom-left corner
    active = (height-1)*width;
    GetNode(active)->AddNeighbour(GetNode(active-width));//above
    GetNode(active)->AddNeighbour(GetNode(active+1));    //to the right

    //bottom row
    for (int i = 1; i < (width-1); i++)
    {
        active = i + (height-1)*width;
        GetNode(active)->AddNeighbour(GetNode(active-1)); //to the left
        GetNode(active)->AddNeighbour(GetNode(active+1)); //to the right
        GetNode(active)->AddNeighbour(GetNode(active-width)); //above
    }

    //bottom-right corner
    active = height*width - 1;
    GetNode(active)->AddNeighbour(GetNode(active-width));//above
    GetNode(active)->AddNeighbour(GetNode(active-1));    //to the left
}

void SquareGrid::Draw(QPainter *painter, int visWidth, int visHeight)
{

    double cellWidth = double(visWidth-1)/GetWidth();
    double cellHeight= double(visHeight-1)/GetHeight();

    QPen pen;
    QBrush brush;

    //variables to track accumulated difference in width/height
    //of cells to fill screen.
    double dW(cellWidth - trunc(cellWidth));
    double dH(cellHeight - trunc(cellHeight));

    double errW(dW);
    int iX(0);
    for (int i = 0; i < GetWidth(); i++)
    {
        int itrWidth = trunc(cellWidth) + trunc(errW);
        int jY(0);
        double errH(dH);

        for (int j = 0; j < GetHeight(); j++)
        {
            int itrHeight = trunc(cellHeight) + trunc(errH);

            painter->setBrush(GetBrush(i,j));
            painter->drawRect(iX,jY,itrWidth, itrHeight);
            //Make cells one pixel bigger if amount lost in truncation
            //is greater than 1.

            jY += itrHeight;
            errH += dH - trunc(errH);
        }

        iX += itrWidth;
        errW += dW -  trunc(errW);
    }
}






