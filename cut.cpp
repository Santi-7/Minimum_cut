/** ---------------------------------------------------------------------------
 ** cut.cpp
 ** An implementation for Karger's and Karger-Stein's algorithm to find the
 ** minimum cut of a graph. It's ready to try different random number generators
 ** and see the differences between the results they provide.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <KargerGraph.hpp>

#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>

#define RANDOM MERSENNE

using namespace std;

/**
 * Removes the spaces before and after a string.
 * @author StackOverflow user: @elxala from
 *      http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring#217605
 *
 * @param str Input string from which spaces will be removed.
 * @return string without leading or treading spaces.
 */
string& trimSpaces(string &str)
{
    // right trim.
    while ((str.length() > 0) & (((str[str.length()-1] == ' ') |
            (str[str.length()-1] == '\t') |
            (str[str.length()-1] == '\n'))))
        str.erase(str.length()-1, 1);

    // left trim.
    while ((str.length() > 0) & (((str[0] == ' ') |
            (str[0] == '\t') |
            (str[0] == '\n'))))
        str.erase(0, 1);
    return str;
}

/**
 * Reads a graph from a product file. The file format is:
 * <Number of products>
 * <Product name>+ // One each line. Vertex in the graph.
 * <Product name>|<Product name> // One each line. Edge in the graph.
 *
 * @param filename Path to the file from which the graph will be loaded.
 * @param readWeightedGraph True if the graph to read is weighted.
 * @return Map of the products read and the constructed Karger's Graph.
 */
tuple<unordered_map<string, Product>, KargerGraph> readFile(const string& filename, const bool readWeightedGraph)
{
	// Open the input file.
    ifstream file(filename);
    if (!file.good())
    {
        cerr << "Unable to open the file '" << filename << "'." << endl;
        throw 1;
    }

    // Map that manages the Amazon's products.
    unordered_map<string, Product> productMap;
    // Karger's Graph.
	KargerGraph kargerGraph(readWeightedGraph);

    int numberOfProducts;
    file >> numberOfProducts;

    // Read all the products in the input file.
    while (numberOfProducts --> 0)
    {
        string productName;
        getline(file, productName);
        productName = trimSpaces(productName);
        // If the line is empty skip it
        if (productName.size() == 0)
        {
            numberOfProducts++; continue;
        }
        bool emplacedCorrectly = get<1>(productMap.emplace(productName, Product(productName)));
        if (!emplacedCorrectly) { cerr << "Error inserting product in the map.\n"; throw 1; }
        kargerGraph.AddProduct(&productMap[productName]);
    }

    string weight;
    // Read all the edges in the input file.
    while (file.good())
    {
        string productName1, productName2;
        getline(file, productName1, '|');
        getline(file, productName2, '|');
        productName1 = trimSpaces(productName1);
        productName2 = trimSpaces(productName2);
        getline(file, weight);
        if ((productName1.size() == 0) | (productName2.size() == 0))
            continue;
        if ((productMap.find(productName1) == productMap.end()) |
            (productMap.find(productName2) == productMap.end()))
        {
            cerr << "Wrong product name, all product names must appear before their connections are defined.\n";
            throw 1;
        }
        // The pointers to the products are unique, so they can be the packs' id.
        Edge theNewEdge(static_cast<unsigned int>(&productMap[productName1]),
                        static_cast<unsigned int>(&productMap[productName2]),
                        atoi(weight)); // TODO: Not always a weight.
        kargerGraph.AddEdge(theNewEdge);
    }

    return make_tuple(productMap, kargerGraph);
}

/**
 * @param from Minimum value that can be returned.
 * @param to Maximum value that can be returned.
 * @return Random value in the specified range.
 */
unsigned int getRandom(unsigned int from, unsigned int to)
{
#if RANDOM == MERSENNE
    static random_device rd;     // only used once to initialise (seed) engine
    static mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(from, to); // guaranteed unbiased
    return (unsigned int) uni(rng);
#elif RANDOM == C
    return rand();
#endif
}

/**
 * An implementation of Karger's algorithm.
 * @param nodes Vertices of the graph for which a cut will be returned
 * @param edges Edges of the graph for which a cut will be returned
 * @return Possible minimum cut for the input graph. It's not guaranteed to be correct. nodes
 *  and edges will be updated so that nodes contains only two vectors of vertices and edges only
 *  the edges remaining in the cut found.
 */
unsigned int Karger(NodeList& nodes, EdgeList& edges, unsigned int t = 2)
{
    while(nodes.size() > t)
    {
        // Choose a random edge.
        unsigned int chosenEdgeIndex = getRandom(0, static_cast<unsigned int>(edges.size() - 1));
        unsigned int receivingNode = get<0>(edges[chosenEdgeIndex]);
        unsigned int absorbedNode = get<1>(edges[chosenEdgeIndex]);
        unsigned int receivingNodeIndex = 0;
        unsigned int absorbedNodeIndex = 0;
        unsigned int endEarly = 0;
        // Fuse the two nodes of the edges into one. For efficiency, fuse one (absorbedNode) into
        // another (receivingNode).
        for (unsigned int i = 0; (i < nodes.size()) & (endEarly < 2); ++i)
        {
            if (nodes[i][0] == receivingNode) { receivingNodeIndex = i; endEarly++; }
            else if (nodes[i][0] == absorbedNode) { absorbedNodeIndex = i; endEarly++; }
        }
        nodes[receivingNodeIndex].insert(nodes[receivingNodeIndex].end(), nodes[absorbedNodeIndex].begin(), nodes[absorbedNodeIndex].end());
        nodes.erase(nodes.begin() + absorbedNodeIndex);
        edges.erase(edges.begin() + chosenEdgeIndex);

        // Remove self-loop edges.
        for (auto it = edges.begin(); it < edges.end(); ++it)
        {
            if (get<0>(*it) == absorbedNode) *it = make_tuple(receivingNode, get<1>(*it));
            else if (get<1>(*it) == absorbedNode) *it = make_tuple(get<0>(*it), receivingNode);
            if (get<0>(*it) == get<1>(*it))
            {
                it = edges.erase(it);
                --it;
            }
        }
    }
    // Return the min cut, this is, the number of edges still remaining in the graph.
    return static_cast<unsigned int>(edges.size());
}

/**
 * Karger-Stein's Min-Cut algorithm
 * @param nodes Vertices of the graph for which a cut will be returned
 * @param edges Edges of the graph for which a cut will be returned
 * @return Possible minimum cut for the input graph. It's not guaranteed to be correct. nodes
 *  and edges will be updated so that nodes contains only two vectors of vertices and edges only
 *  the edges remaining in the cut found. It's more likely to get the minimum cut than Karger's
 *  algorithm but also takes longer to run.
 */
unsigned int Karger_Stein(NodeList& nodes, EdgeList& edges)
{
#if RANDOM == C
    srand(static_cast<unsigned int>(time(NULL)));
#endif

    if (nodes.size() < 6)
    {
        return Karger(nodes, edges, 2);
    }
    else
    {
        unsigned int t = 1 + static_cast<unsigned int>(ceil(nodes.size() / sqrt(2)));
        NodeList nodes2(nodes);
        EdgeList edges2(edges);
        Karger(nodes, edges, t);
        Karger(nodes2, edges2, t);
        unsigned int cut1 = Karger_Stein(nodes, edges);
        unsigned int cut2 = Karger_Stein(nodes2, edges2);
        if (cut1 < cut2)
        {
            return cut1;
        }
        else
        {
            nodes = nodes2;
            edges = edges2;
            return cut2;
        }
    }
}

/**
 * Read file from parameters and run Karger's algorithm on the graph described in it.
 */
int main(int argc, char * argv[])
{
    // Check number of parameters.
	if (argc < 2)
    {
        cout << "Wrong number of arguments, at least one needed." << endl;
        cout << "Usage: " << argv[0] << " <products_file> [-ks] [-w]" << endl;
        cout << "If the option -ks is used then the algorithm run will be Karger-Stein's." << endl;
        cout << "If the option -w is used then the product file will be treated as a weighted graph." << endl;
        return 1;
    }
    bool useKargerStein = false;
    bool weightedGraph = false;
    for (int i = 2; i < argc; ++i)
    {
	    string tmpArg = string(argv[i]);
	    if (tmpArg == "-ks") useKargerStein = true;
	    else if (tmpArg == "-w") weightedGraph = true;
    }

    // Construct the data structure.
    unordered_map<string, Product> productMap;
    KargerGraph kargerGraph;
	tie(productMap, kargerGraph) = readFile(string(argv[1]), weightedGraph);

    // Call Karger's algorithm, or its enhanced version Karger-Stein.
    unsigned int minimumCut;
    //if (useKargerStein) minimumCut = Karger_Stein(nodes, edges);
    //else minimumCut = Karger(nodes, edges);

    unsigned long vertices = productMap.size();
    while (vertices --> 2) kargerGraph.FuseStep();

    // Show results.
    cout << "The min cut is " << kargerGraph.GetEdges().size() << ".\n\n";
    for (pair<unsigned int, ProductsPack> pack : kargerGraph.GetPacks()) pack.second.Print();
}