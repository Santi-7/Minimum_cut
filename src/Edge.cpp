/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for Edge class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "Edge.hpp"

Edge::Edge(const std::shared_ptr<ProductsPack>& p1, const std::shared_ptr<ProductsPack>& p2) : mP1(p1), mP2(p2) {}
