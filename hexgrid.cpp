#include "hexgrid.h"

#include <QDebug>


HexGrid::HexGrid(QWidget* parent)
    : Grid(parent) {}

HexGrid::HexGrid(QWidget* parent, int width, int height)
    : Grid(parent, width, height)
{
    FillNodes();
    DefineNeighbours();
}

void HexGrid::FillNodes()
{
    //Add nodes
    int nNodes = GetWidth()*GetHeight();

    for (int i = 0; i < nNodes; i++)
        AddNode(new Node(i));
}

void HexGrid::DefineNeighbours()
{
    int width(GetWidth()), height(GetHeight());
    int active;

    //"even-r" hexagonal grid layout, meaning
    //odd rows are offset from the left hand
    //side by half a hexagon. See:
    //https://www.redblobgames.com/grids/hexagons/

    //top-left corner:
    active = 0;
    GetNode(active)->AddNeighbour(GetNode(active+1));     //to the right
    GetNode(active)->AddNeighbour(GetNode(active+width)); //below
    GetNode(active)->AddNeighbour(GetNode(active+width+1)); //1 right,1 below

    //top row:
    for (int i = 1; i < (width-1); i++)
    {
        //(active = i)
        GetNode(i)->AddNeighbour(GetNode(i-1)); //to the left
        GetNode(i)->AddNeighbour(GetNode(i+1)); //to the right
        GetNode(i)->AddNeighbour(GetNode(i+width)); //below
        GetNode(i)->AddNeighbour(GetNode(i+width+1)); //1 right,1 below
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
        if (j % 2 == 0) //even row no.
        {
            GetNode(active)->AddNeighbour(GetNode(active-width+1));
                //1 above, 1 right
            GetNode(active)->AddNeighbour(GetNode(active+width+1));
                //1 below, 1 right
        }
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
        if (j % 2 == 0) //even row no.
        {
            GetNode(active)->AddNeighbour(GetNode(active-width+1));
                //1 above, 1 right
            GetNode(active)->AddNeighbour(GetNode(active+width+1));
                //1 below, 1 right
        }
        else //odd row no.
        {
            GetNode(active)->AddNeighbour(GetNode(active-width-1));
                //1 above, 1 left
            GetNode(active)->AddNeighbour(GetNode(active+width-1));
                //1 below, 1 left
        }
    }

    //right column
    for (int j = 1; j < (height-1); j++)
    {
        active = (j+1)*width - 1;
        GetNode(active)->AddNeighbour(GetNode(active-width)); //above
        GetNode(active)->AddNeighbour(GetNode(active-1));     //to the left
        GetNode(active)->AddNeighbour(GetNode(active+width)); //below
        if (j % 2 == 1) //odd row no.
        {
            GetNode(active)->AddNeighbour(GetNode(active-width-1));
                //1 above, 1 left
            GetNode(active)->AddNeighbour(GetNode(active+width-1));
                //1 below, 1 left
        }
    }

    //bottom-left corner
    active = (height-1)*width;
    GetNode(active)->AddNeighbour(GetNode(active-width));//above
    GetNode(active)->AddNeighbour(GetNode(active+1));    //to the right
    if (height % 2 == 0) //even row no.
        GetNode(active)->AddNeighbour(GetNode(active-width+1));
            //1 above, 1 right

    //bottom row
    for (int i = 1; i < (width-1); i++)
    {
        active = i + (height-1)*width;
        GetNode(active)->AddNeighbour(GetNode(active-1)); //to the left
        GetNode(active)->AddNeighbour(GetNode(active+1)); //to the right
        GetNode(active)->AddNeighbour(GetNode(active-width)); //above
        if (height % 2 == 0) //even row no.
            GetNode(active)->AddNeighbour(GetNode(active-width+1));
                //1 above, 1 right
        else //odd row no.
            GetNode(active)->AddNeighbour(GetNode(active-width-1));
                //1 above, 1 left
    }

    //bottom-right corner
    active = height*width-1;
    GetNode(active)->AddNeighbour(GetNode(active-width));//above
    GetNode(active)->AddNeighbour(GetNode(active-1));    //to the left
    if (height % 2 == 1) //odd row no.
        GetNode(active)->AddNeighbour(GetNode(active-width-1));
    //1 above, 1 left
}

void HexGrid::Draw(QPainter *painter, int visWidth, int visHeight)
{
    //Hexagon geometry is somewhat complex, and horizontal and vertical
    //parameters are not symmetric in chosen grid layout...
    double x = double(visWidth-1)/(2*GetWidth()+1);
    double y = double(visHeight-1)/(3*GetHeight()+1);
    //these are some fundamental width and height units. The width of one
    //hexagon is 2x, and the height is 4y.

    double dX(x - trunc(x));
    double dY(y - trunc(y));



    //2d vector to define vertex locations:
    std::vector<std::vector<QPoint> > vertices;

    int jY(0);
    double errY(dY);
    for (int j = 0; j <= 3*GetHeight()+1; j++)
    {
        double errX(dX);
        int iX = 0;
        int itrY = trunc(y) + trunc(errY);

        vertices.push_back(std::vector<QPoint>());

        for (int i = 0; i <= 2*GetWidth()+1; i++)
        {
            int itrX = trunc(x) + trunc(errX);

            vertices[j].push_back(QPoint(iX,jY));

            iX += itrX;
            errX += dX - trunc(errX);
        }
        jY += itrY;
        errY += dY - trunc(errY);
    }

    for (int j = 0; j < 3*GetHeight()-2;j+=3)
    {
        int i0 = (j%2==0) ? 1:0;
        for (int i = i0; i < 2*GetWidth()-1+i0; i+=2)
        {
            QPolygon hex;
            hex << vertices[j][i+1]   //top of hexagon
                << vertices[j+1][i+2]  //upper-right
                << vertices[j+3][i+2]   //lower-right
                << vertices[j+4][i+1]   //bottom
                << vertices[j+3][i]     //lower-left
                << vertices[j+1][i];    //upper-left
            painter->setBrush(GetBrush(i/2,j/3));
            painter->drawPolygon(hex);
        }
    }

}







//void oldDraw(QPainter *painter, int visWidth, int visHeight)
//{

//    //Hexagon geometry is somewhat complex, and horizontal and vertical
//    //parameters are not symmetric in chosen grid layout...
//    double x = double(visWidth-1)/(2*GetWidth()+1);
//    double y = double(visHeight-1)/(3*GetHeight()+1);
//    //these are some fundamental width and height units. The width of one
//    //hexagon is 2x, and the height is 4y.

//    double dX(x - trunc(x));
//    double dY(y - trunc(y));


//    int jY(0);
//    double errY(dY);

//    for (int j = 0; j < GetHeight(); j++)
//    {
//        double errX(dX);
//        int iX = (j%2 == 0) ? trunc(x) : 0; //offset even rows
//        int itrY = trunc(y) + trunc(errY);
//        for (int i = 0; i < GetWidth(); i++)
//        {
//            int itrX = trunc(x) + trunc(errX);

//            QPolygon hex;
//            hex << QPoint(iX + itrX, jY)            //top of hexagon
//                << QPoint(iX + 2*itrX, jY + itrY)   //upper-right
//                << QPoint(iX + 2*itrX, jY + 3*itrY) //lower-right
//                << QPoint(iX + itrX, jY + 4*itrY)   //bottom
//                << QPoint(iX, jY + 3*itrY)          //lower-left
//                << QPoint(iX, jY + itrY);           //upper-left
//            painter->setBrush(GetBrush(i,j));
//            painter->drawPolygon(hex);
//            //Make cells one pixel bigger if amount lost in truncation
//            //is greater than 1.
//            iX += 2*itrX;
//            errX += dX - trunc(errX);
//        }
//        jY += 3*itrY;
//        errY += dY - trunc(errY);
//    }


//}
