#include "../header/NodeInfo.h"

NodeInfo::NodeInfo(float weight)
{
    this->weight = weight;
}

float NodeInfo::getWeight()
{
    return this->weight;
}

void NodeInfo::setWeight(float weight)
{
    this->weight = weight;
}
