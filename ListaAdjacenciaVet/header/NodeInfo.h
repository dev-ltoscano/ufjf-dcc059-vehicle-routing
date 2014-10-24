#ifndef NODEINFO_H_INCLUDED
#define NODEINFO_H_INCLUDED

class NodeInfo
{
    private:
        float weight;
    public:
        NodeInfo(float weight);

        float getWeight();
        void setWeight(float weight);
};

#endif // NODEINFO_H_INCLUDED
