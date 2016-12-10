/** ---------------------------------------------------------------------------
 ** main.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <memory>
#include <vector>

using namespace std;

int main()
{
    KargerGraph kargerGraph();
    // TODO: Read products and edges from file.
    /* TODO: Construct a hash table with all the products.
     * TODO:           a Kargers' Graph
     */
    // TODO: Karger's algorithm.
}

class KargerGraph
{

public:

    /**
     * Adds the Amazon's product [product] to the Karger's Graph as a vertice.
     *
     * @param product to be added to the Karger's Graph as a vertice.
     */
    void AddProduct(shared_ptr<Product> product)
    {
        ProductsPack pack(product);
        mPacks.push_back(pack);
        // TODO: Fill the future attribute mPack of product.
        // TODO: Fill previousPack and nexPack of [pack].
    }

    /**
     * Adds the Edge [edge] to the Karger's Graph as an edge.
     *
     * @param edge to be added to the Karger's Graph as an edge.
     */
    void AddEdge(Edge edge)
    {
        mEdges.push_back(edge);
        // TODO: Add shared_ptr of this edge to the packs of mP1, mP2.
    }

private:

    /** Packs of Amazon's products (vertices of the graph). */
    vector<ProductsPack> mPacks;

    /** Edges between the packs (edges of the graph). */
    vector<Edge> mEdges;
};

/**
 * This class represents an Amazon's product.
 */
class Product
{

public:

    /**
     * Creates an Amazon's product with name [name].
     *
     * @param name of the Amazon's product created.
     * @return an Amazon's product with name [name].
     */
    Product(const string &name)
    : mName(name) {}

private:

    /** Name of the Amazon's product. */
    string mName;
};

/**
 * An edge between two packs of Amazon's products, [mP1] and [mP2], means
 * that at least one product of each pack have been bought together at least once.
 */
class Edge
{

public:

    /**
     * Creates an edge between the two packs of Amazon's products [p1] and [p2].
     *
     * @param p1 First pack of Amazon's product.
     * @param p2 Second pack of Amazon's product.
     * @return an edge between the two packs of Amazon's products [p1] and [p2].
     */
    Edge(const shared_ptr<ProductsPack> &p1, const shared_ptr<ProductsPack> &p2)
    : mP1(p1), mP2(p2) {}

private:

    /** Packs of Amazon's products whose products, at least one, have been bought together. */
    shared_ptr<ProductsPack> mP1, mP2;
};

/**
 * This class represents a pack of Amazon's products.
 */
class ProductsPack
{

public:

    /**
     * Creates a pack of products with an initial product [initialProduct].
     *
     * @param initialProduct of the pack.
     * @return a pack of products with an initial product [initialProduct].
     */
    ProductsPack(const shared_ptr<Product> initialProduct)
    {
        mProducts.push_back(initialProduct);
    }

    /**
     * Adds the Edge [edge] to this pack.
     *
     * @param edge to be added to this pack.
     */
    void AddEdge(const shared_ptr<Edge> edge)
    {
        mEdges.push_back(edge);
    }

private:

    /** Amazon's products that belong to this pack. */
    vector<shared_ptr<Product>> mProducts;

    /** Packs of Amazon's products whose products, at least one, have been
     * bought with, at least, one product of this pack at least once. */
    vector<shared_ptr<Edge>> mEdges;

    /** In order to manage O(1) when deleting (fusing) a ProductsPack from a vector,
     * a ProductsPack has these two pointers to the previous and next pack in the vector.
     * Note: they will have to be filled when inserting the pack into the vector. */
    shared_ptr<ProductsPack> previousPack, nextPack;
};