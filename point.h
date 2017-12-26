#ifndef POINT_H
#define POINT_H


class Point
{
public:
    //Constructors
    Point();
    Point(int x, int y);
    Point(const int*); //from an array
    Point(const Point&);

    //Destructor
    virtual ~Point();

    //Access Methods:
    inline double x()  const { return fX; }
    inline double y()  const { return fY; }
    inline double X()  const { return fX; }
    inline double Y()  const { return fY; }

    inline void SetX(int xx) { fX = xx; }
    inline void SetY(int yy) { fY = yy; }
    inline void SetXY(int xx, int yy) { fX = xx; fY = yy; }
    inline void SetXY(const Point& p) { fX = p.fX; fY = p.fY; }

    //Translation
    void Translate(int xx, int yy) { fX += xx; fY += yy; }
    void Translate(const Point& p) { fX += p.fX; fY += p.fY; }

    //Print
    void Print() const;



    //Will add other methods when needed.

private:
    int fX,fY;

};

//Operators
bool operator == (const Point&, const Point&);

#endif // POINT_H
