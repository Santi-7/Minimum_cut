/** ---------------------------------------------------------------------------
 ** Edge.cpp
 ** Implementation for Edge class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "Edge.hpp"

Edge::Edge(ProductsPack *p1, ProductsPack *p2)
: mP1(p1), mP2(p2) {}

ProductsPack* Edge::GetPack1() const
{
    return mP1;
}

ProductsPack* Edge::GetPack2() const
{
    return mP2;
}

void Edge::SetPack1(ProductsPack *pack)
{
    mP1 = pack;
}

void Edge::SetPack2(ProductsPack *pack)
{
    mP2 = pack;
}

unsigned long Edge::GetPosition() const
{
    return mPosition;
}

void Edge::SetPosition(const unsigned long position)
{
    mPosition = position;
}

bool operator==(const Edge &edge1, const Edge &edge2)
{
    return ((edge1.mP1 == edge2.mP1) & (edge1.mP2 == edge2.mP2)) |
           ((edge1.mP1 == edge2.mP2) & (edge1.mP2 == edge2.mP1));
}