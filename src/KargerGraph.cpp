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
    // It's the first pack added to the graph.
    if (mPacks.IsEmpty()) {
        mPacks = pack;
    }
    // There are already packs added in the graph.
    else {
        // The previous pack of the first one marks the last pack in the array.
        mPacks.GetPrevious()->SetNext(std::make_shared(pack));
        pack.SetPrevious(mPacks.GetPrevious());
    }
    /* Update the previous pack of the first one in the array (which marks
     * the last pack in the array) to the new one. */
    mPacks.SetPrevious(std::make_shared(pack));
    // Set the created pack to the product to fill later the graph correctly.
    product->SetPack(std::make_shared(pack));
}

void KargerGraph::AddEdge(Edge edge)
{
    mEdges.push_back(edge);
}