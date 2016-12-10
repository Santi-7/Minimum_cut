/** ---------------------------------------------------------------------------
 ** Edge.cpp
 ** Implementation for Edge class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "Edge.hpp"

Edge::Edge(const std::shared_ptr<ProductsPack> &p1,
           const std::shared_ptr<ProductsPack> &p2)
: mP1(p1), mP2(p2) {}

std::shared_ptr<ProductsPack> Edge::GetPack1() const
{
    return mP1;
}

std::shared_ptr<ProductsPack> Edge::GetPack2() const
{
    return mP2;
}

void Edge::SetPack1(std::shared_ptr<ProductsPack> pack)
{
    mP1 = pack;
}

void Edge::SetPack2(std::shared_ptr<ProductsPack> pack)
{
    mP2 = pack;
}

bool operator==(const Edge &edge1, const Edge &edge2)
{
    return ((edge1.mP1 == edge2.mP1) & (edge1.mP2 == edge2.mP2)) |
           ((edge1.mP1 == edge2.mP2) & (edge1.mP2 == edge2.mP1));
}