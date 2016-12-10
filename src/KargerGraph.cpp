/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

#include <stdlib.h>

KargerGraph::KargerGraph()
{
    // Initializes the random numbers generator's seed.
    srand(time(NULL));
}

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

void KargerGraph::FuseStep()
{
    // Get a random edge of the graph.
    Edge randomEdge = mEdges[rand() % mEdges.size()];
    // Fuses the products of both packs into the first one.
    randomEdge.GetPack1()->AddProducts(randomEdge.GetPack2()->GetProducts());
    // Fuses the edges of both packs into the first one.
    std::vector<std::shared_ptr<Edge>> edges = randomEdge.GetPack2()->GetEdges();
    for (const std::shared_ptr<Edge> edge : edges)
    {
        // Remove this edge (it will be a self-loop edge otherwise).
        if (*edge == randomEdge)
        {
            // TODO: Delete this edge.
            ;
        }
        else // edge != randomEdge
        {
            // Change the own pack vertice of the edge to the fused one.
            if (edge->GetPack1() == randomEdge.GetPack2())
            {
                edge->SetPack1(randomEdge.GetPack1());
            }
            else // edge->GetPack1() != randomEdge.GetPack2()
            {
                edge->SetPack2(randomEdge.GetPack1());
            }
            // Add the edge to the fused one.
            randomEdge.GetPack1()->AddEdge(edge);
        }
    }
}