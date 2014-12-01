#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include <iostream>

using namespace std;

class Vehicle
{
    private:
        int id;
        float initialCapacity;
        float capacity;
        int currentPosition;
    public:
        Vehicle(int id, float initialCapacity, int currentPosition);

        int getId();

        float getInitialCapacity();
        float getCapacity();
        void addCapacity(float increase);
        void removeCapacity(float decrease);
        void resetCapacity();

        int getCurrentPosition();
        void setCurrentPosition(int nodeId);
};

#endif // VEHICLE_H_INCLUDED
