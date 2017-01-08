/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

#include <assert.h>
#include <valarray>

KargerGraph::KargerGraph(const bool isWeighted, RandomNumberEngine &rng)
: mIsWeighted(isWeighted), mRng(rng), mSumWeights(0)
{}

KargerGraph::KargerGraph(const KargerGraph &copy, RandomNumberEngine &rng)
: mPacks(copy.mPacks), mEdges(copy.mEdges),
  mIsWeighted(copy.mIsWeighted), mRng(rng), mSumWeights(copy.mSumWeights)
{}

void KargerGraph::AddProduct(Product *product)
{
    // Add the pack to the map of packs.
    mPacks.emplace(product->GetId(), ProductsPack(product));
}

void KargerGraph::AddEdge(Edge &edge)
{
    // Add it to the vector of edges.
    mEdges.push_back(edge);
    mSumWeights += edge.GetWeight();
}

void KargerGraph::FuseStep()
{
    // Avoid division by zero.
    assert(mEdges.size() > 0);

    // Get a random edge of the graph.
    Edge randomEdge;
    if (mIsWeighted)
    {
        unsigned int random = mRng.GetRandom(0, static_cast<unsigned int>(mEdges.size()));
        unsigned int acum = 0;
        // Get the immediate edge that overpass the random value.
        for (unsigned int i = 0; i < mEdges.size(); ++i)
        {
            acum += mEdges[i].GetWeight();
            if (acum > random)
            {
                randomEdge = mEdges[i];
                break;
            }
        }
    }
    else
    {
        randomEdge = mEdges[mRng.GetRandom(0, static_cast<unsigned int>(mEdges.size()))];
    }

    // Fuses the products of both packs into the first one.
    mPacks[randomEdge.GetPack1()].AddProducts(mPacks[randomEdge.GetPack2()].mProducts);

    for (auto it = mEdges.begin(); it < mEdges.end(); ++it)
    {
        // Remove self-loop edges.
        if (randomEdge == *it)
        {
            mSumWeights -= it->GetWeight();
            it = mEdges.erase(it);
        }
        // Update edges of the deleted node to the new fused node.
        if (it->GetPack1() == randomEdge.GetPack2())
            it->SetPack1(randomEdge.GetPack1());
        else if (it->GetPack2() == randomEdge.GetPack2())
            it->SetPack2(randomEdge.GetPack1());
    }

    /* Remove randomEdge.GetPack2() from mPacks. */
    mPacks.erase(randomEdge.GetPack2());
}

unsigned int KargerGraph::KargerAlgorithm(unsigned int t)
{
    // Fuse until t (2 by default) nodes are remaining.
    unsigned long vertices = mPacks.size();
    while (vertices --> t) FuseStep();

    // Return the weights of the remaining edges.   Weighted graph.
    if (mIsWeighted) return mSumWeights;
    // Return the remaining edges.                  Unweighted graph.
    else return static_cast<unsigned int>(mEdges.size());
}

unsigned int KargerGraph::KargerSteinAlgorithm()
{
    if (mPacks.size() < 6)
    {
        return KargerAlgorithm();
    }
    else
    {
        unsigned int t = 1 + static_cast<unsigned int>(std::ceil(mPacks.size() / std::sqrt(2)));
        KargerGraph copy(*this);
        KargerAlgorithm(t);
        copy.KargerAlgorithm(t);
        unsigned int cut1 = KargerSteinAlgorithm();
        unsigned int cut2 = copy.KargerSteinAlgorithm();
        if (cut1 <= cut2)
        {
            return cut1;
        }
        else
        {
            // Return state to the copy graph.
            mPacks = copy.mPacks;
            mEdges = copy.mEdges;
            mIsWeighted = copy.mIsWeighted;
            mSumWeights = copy.mSumWeights;
            return cut2;
        }
    }
}

std::map<unsigned int, ProductsPack> KargerGraph::GetPacks() const
{
    return mPacks;
}

std::vector<Edge> KargerGraph::GetEdges() const
{
    return mEdges;
}