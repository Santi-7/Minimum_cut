/** ---------------------------------------------------------------------------
 ** Edge.cpp
 ** Implementation for Edge class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "Edge.hpp"

Edge::Edge(Product *p1, Product *p2, const unsigned int weight)
: mP1(p1), mP2(p2), mWeight(weight) {}

Product* Edge::GetPack1() const
{
    return mP1;
}

Product* Edge::GetPack2() const
{
    return mP2;
}

void Edge::SetPack1(Product *pack)
{
    mP1 = pack;
}

void Edge::SetPack2(Product *pack)
{
    mP2 = pack;
}

bool operator==(const Edge &edge1, const Edge &edge2)
{
    return ((edge1.mP1 == edge2.mP1) & (edge1.mP2 == edge2.mP2)) |
           ((edge1.mP1 == edge2.mP2) & (edge1.mP2 == edge2.mP1));
}