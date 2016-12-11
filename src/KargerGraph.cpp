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
    // Add the pack to the vector of packs.
    mPacks.push_back(ProductsPack(product));
    mPacks[mPacks.size()-1].SetPosition(mPacks.size()-1);

    // Set the created pack to the product to fill later the edges correctly.
    product->SetPack(std::shared_ptr<ProductsPack>(&mPacks[mPacks.size()-1]));
}

void KargerGraph::AddEdge(Edge &edge)
{
    // Add it to the vector of edges.
    edge.SetPosition(mEdges.size());
    mEdges.push_back(edge);

    // Add this edge to both packs.
    std::shared_ptr<Edge> pEdge = std::shared_ptr<Edge>(&mEdges[mEdges.size()-1]);
    pEdge->GetPack1()->AddEdge(pEdge);
    pEdge->GetPack2()->AddEdge(pEdge);
}

void KargerGraph::FuseStep()
{
    // Avoid division by zero.
    assert(mEdges.size() > 0);
    // Get a random edge of the graph.
    Edge randomEdge = mEdges[rand() % mEdges.size()];
    // Fuses the products of both packs into the first one.
    randomEdge.GetPack1()->AddProducts(randomEdge.GetPack2()->mProducts);
    // Remove self-loop edges from first pack.
    for (unsigned long i(0); i < randomEdge.GetPack1()->mEdges.size(); ++i)
    {
        if (*randomEdge.GetPack1()->mEdges[i] == randomEdge)
        {
            randomEdge.GetPack1()->mEdges[i] = randomEdge.GetPack1()->mEdges[randomEdge.GetPack1()->mEdges.size()-1];
            randomEdge.GetPack1()->mEdges.pop_back();
        }
    }
    // Fuses the edges of both packs into the first one.
    for (std::shared_ptr<Edge> edge : randomEdge.GetPack2()->mEdges)
    {
        // Remove this edge (it will be a self-loop edge otherwise).
        if (*edge == randomEdge)
        {
            /* To manage O(1), put the last edge of the vector in the position of the
             * deleted edge, and pop the last edge. */
            mEdges[mEdges.size()-1].SetPosition(edge->GetPosition());
            mEdges[edge->GetPosition()] = mEdges[mEdges.size()-1];
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