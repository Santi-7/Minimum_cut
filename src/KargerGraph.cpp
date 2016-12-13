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

void KargerGraph::AddProduct(Product *product)
{
    // Add the pack to the vector of packs.
    mPacks.push_back(ProductsPack(product));
    mPacks.back().SetPosition(mPacks.size()-1);

    // Set the created pack to the product to fill later the edges correctly.
    product->SetPack(&mPacks.back());
}

void KargerGraph::AddEdge(Edge &edge)
{
    // Add it to the vector of edges.
    edge.SetPosition(mEdges.size());
    mEdges.push_back(edge);

    // Add this edge to both packs.
    Edge *pEdge = &mEdges.back();
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
    unsigned long packSize = randomEdge.GetPack1()->mEdges.size();
    for (unsigned long i(0); i < packSize; ++i)
    {
        if (*randomEdge.GetPack1()->mEdges[i] == randomEdge)
        {
            randomEdge.GetPack1()->mEdges[i] = randomEdge.GetPack1()->mEdges.back();
            randomEdge.GetPack1()->mEdges.pop_back();
        }
    }
    // Fuses the edges of both packs into the first one.
    for (Edge *edge : randomEdge.GetPack2()->mEdges)
    {
        // Remove this edge (it will be a self-loop edge otherwise).
        if (*edge == randomEdge)
        {
            // Update the pointers (in both packs) to the last edge to the new position.
            for (unsigned long i(0); i < mEdges.back().GetPack1()->mEdges.size(); ++i)
            {
                if (mEdges.back().GetPack1()->mEdges[i] == &mEdges.back())
                {
                    mEdges.back().GetPack1()->mEdges[i] = &mEdges[edge->GetPosition()];
                    break;
                }
            }
            for (unsigned long i(0); i < mEdges.back().GetPack2()->mEdges.size(); ++i)
            {
                if (mEdges.back().GetPack2()->mEdges[i] == &mEdges.back())
                {
                    mEdges.back().GetPack2()->mEdges[i] = &mEdges[edge->GetPosition()];
                    break;
                }
            }
            /* To manage O(1), put the last edge of the vector in the position of the
             * deleted edge, and pop the last edge. */
            mEdges.back().SetPosition(edge->GetPosition());
            mEdges[edge->GetPosition()] = mEdges.back();
            mEdges.pop_back();
        }
        else // edge != randomEdge
        {
            // Change the own pack vertice of the edge to the fused one.
            if (edge->GetPack1() == randomEdge.GetPack2())
                edge->SetPack1(randomEdge.GetPack1());
            else // edge->GetPack1() != randomEdge.GetPack2()
                edge->SetPack2(randomEdge.GetPack1());
            // Add the edge to the fused one.
            randomEdge.GetPack1()->AddEdge(edge);
        }
    }
    /* Remove randomEdge.GetPack2() from mPacks. */
    // Update the pointers of the edges to the new position of the pack.
    for (Edge *edge : mPacks.back().mEdges)
    {
        if (edge->GetPack1() == &mPacks.back())
            edge->SetPack1(&mPacks[randomEdge.GetPack2()->GetPosition()]);
        else // (edge->GetPack2() == &mPacks.back())
            edge->SetPack2(&mPacks[randomEdge.GetPack2()->GetPosition()]);
    }
    // Swap pack to delete and the last one.
    mPacks.back().SetPosition(randomEdge.GetPack2()->GetPosition());
    mPacks[randomEdge.GetPack2()->GetPosition()] = mPacks.back();
    // Remove.
    mPacks.pop_back();
}

std::deque<ProductsPack> KargerGraph::GetPacks() const
{
    return mPacks;
}

std::deque<Edge> KargerGraph::GetEdges() const
{
    return mEdges;
}