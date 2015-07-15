#include "../../header/heuristic/Vehicle.h"

Vehicle::Vehicle(int id, int initialCapacity)
{
    this->id = id;
    this->initialCapacity = initialCapacity;
    this->capacity = initialCapacity;
}

int Vehicle::getId()
{
    return this->id;
}

int Vehicle::getInitialCapacity()
{
    return this->initialCapacity;
}

int Vehicle::getCapacity()
{
    return this->capacity;
}

void Vehicle::addCapacity(int increase)
{
	int sum = this->capacity + increase;

    if(sum < this->initialCapacity)
    {
        this->capacity = sum;
    }
}

void Vehicle::removeCapacity(int decrease)
{
	int sum = this->capacity - decrease;

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
