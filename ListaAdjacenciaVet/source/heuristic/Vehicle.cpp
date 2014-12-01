#include "../../header/heuristic/Vehicle.h"

Vehicle::Vehicle(int id, float initialCapacity, int currentPosition)
{
    this->id = id;
    this->initialCapacity = initialCapacity;
    this->capacity = initialCapacity;
    this->currentPosition = currentPosition;
}

int Vehicle::getId()
{
    return this->id;
}

float Vehicle::getInitialCapacity()
{
    return this->initialCapacity;
}

float Vehicle::getCapacity()
{
    return this->capacity;
}

void Vehicle::addCapacity(float increase)
{
    float sum = this->capacity + increase;

    if(sum < this->initialCapacity)
    {
        this->capacity = sum;
    }
}

void Vehicle::removeCapacity(float decrease)
{
    float sum = this->capacity - decrease;

    if(sum > 0)
    {
        this->capacity = sum;
    }
    else
    {
        this->capacity = 0;
    }
}

void Vehicle::resetCapacity()
{
    this->capacity = this->initialCapacity;
}

int Vehicle::getCurrentPosition()
{
    return this->currentPosition;
}

void Vehicle::setCurrentPosition(int currentPosition)
{
    this->currentPosition = currentPosition;
}
