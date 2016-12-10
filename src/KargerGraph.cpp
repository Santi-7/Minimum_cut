/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

void KargerGraph::AddProduct(const std::shared_ptr<Product> &product)
{
    ProductsPack pack(product);
    // It's the first pack added to the graph.
    if (mPacks.IsEmpty()) {
        mPacks = pack;
    }
    // There are already packs added in the graph.
    else {
        // The previous pack of the first one marks the last pack in the array.
        mPacks.GetPrevious()->SetNext(std::make_shared<ProductsPack>(pack));
        pack.SetPrevious(mPacks.GetPrevious());
    }
    /* Update the previous pack of the first one in the array (which marks
     * the last pack in the array) to the new one. */
    mPacks.SetPrevious(std::make_shared<ProductsPack>(pack));
    // Set the created pack to the product to fill later the edges correctly.
    product->SetPack(std::make_shared<ProductsPack>(pack));
}

void KargerGraph::AddEdge(const Edge &edge)
{
    // Add this edge to both packs.
    edge.GetPack1()->AddEdge(std::make_shared<Edge>(edge));
    edge.GetPack2()->AddEdge(std::make_shared<Edge>(edge));
    // Add it to the vector of edges.
    mEdges.push_back(edge);
}