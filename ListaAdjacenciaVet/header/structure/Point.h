#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include <cmath>

using namespace std;

class Point
{
    private:
        float x;
        float y;
    public:
        Point(float x, float y);

        float getCoordX();
        float getCoordY();

        float getDistance(Point *p2);
        bool equals(Point *p2);
};

#endif // POINT_H_INCLUDED
