#include "../../header/structure/Point.h"

Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Point::getCoordX()
{
    return this->x;
}

float Point::getCoordY()
{
    return this->y;
}

float Point::getDistance(Point *p2)
{
    if(p2 != NULL)
    {
        // Distância entre dois pontos
        return sqrt(pow((p2->getCoordX() - this->x), 2) + pow((p2->getCoordY() - this->y), 2));
    }

    return 0;
}

bool Point::equals(Point *p2)
{
    if(p2 != NULL)
    {
        return ((p2->getCoordX() == this->x) && (p2->getCoordY() == this->y));
    }

    return false;
}
