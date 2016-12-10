/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

void KargerGraph::AddProduct(std::shared_ptr<Product> product)
{
    ProductsPack pack(product);
    mPacks.push_back(pack);
    // TODO: Fill the future attribute mPack of product.
    // TODO: Fill previousPack and nexPack of [pack].
}

void KargerGraph::AddEdge(Edge edge)
{
    mEdges.push_back(edge);
    // TODO: Add shared_ptr to this edge to the packs of mP1, mP2.
}

