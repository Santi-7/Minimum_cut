/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

#include <stdlib.h>
#include <assert.h>

KargerGraph::KargerGraph()
{
    // Initializes the random numbers generator's seed.
    srand(time(NULL));
}

void KargerGraph::AddProduct(const std::shared_ptr<Product> &product)
{
    ProductsPack pack(product);
    // Add the pack to the vector of packs.
    pack.SetPosition(mPacks.size());
    mPacks.push_back(pack);
    // Set the created pack to the product to fill later the edges correctly.
    product->SetPack(std::make_shared<ProductsPack>(pack));
}

void KargerGraph::AddEdge(Edge &edge)
{
    // Add this edge to both packs.
    std::shared_ptr<Edge> pEdge(std::make_shared<Edge>(edge));
    edge.GetPack1()->AddEdge(pEdge);
    edge.GetPack2()->AddEdge(pEdge);
    // Updates position of edge in the vector.
    edge.SetPosition(mEdges.size());
    // Add it to the vector of edges.
    mEdges.push_back(edge);
}

void KargerGraph::FuseStep()
{
    // Avoid division by zero.
    assert(mEdges.size() > 0);
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
            /* To manage O(1), put the last edge of the vector in the position of the
             * deleted edge, and pop the last edge. */
            mEdges[edges.size()-1].SetPosition(edge->GetPosition());
            mEdges[edge->GetPosition()] = mEdges[edges.size()-1];
            mEdges.pop_back();
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
    // Remove randomEdge.GetPack2() from mPacks.
    mPacks[mPacks.size()-1].SetPosition(randomEdge.GetPack2()->GetPosition());
    mPacks[randomEdge.GetPack2()->GetPosition()] = mPacks[mPacks.size()-1];
    mPacks.pop_back();
}

std::vector<ProductsPack> KargerGraph::GetPacks() const
{
    return mPacks;
}

std::vector<Edge> KargerGraph::GetEdges() const
{
    return mEdges;
}