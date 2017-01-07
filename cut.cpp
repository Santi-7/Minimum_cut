/** ---------------------------------------------------------------------------
 ** cut.cpp
 ** An implementation for Karger's and Karger-Stein's algorithm to find the
 ** minimum cut of a graph. It's ready to try different random number generators
 ** and see the differences between the results they provide.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>

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

typedef vector<unsigned int> Node;  // A node of the Karger's Graph is a collection of products (their IDs).
typedef vector<Node> NodeList;  // TODO: Change it to map. ID - Node
typedef tuple<unsigned int, unsigned int, unsigned int> Edge;  // Node1, Node2, weight.
typedef vector<Edge> EdgeList;  // Vector of edges.
typedef map<string, unsigned int> ProductList;  // Map of products where key is the product's name.
                                                // A product has also a unique ID.

/**
 * Reads a graph from a product file. The file format is:
 * <Number of products>
 * <Product name>+ // One each line. Vertex in the graph.
 * <Product name>|<Product name> // One each line. Edge in the graph.
 *
 * @param filename path to the file from which the graph will be loaded.
 * @return List of the vertices, edges and a map of product name - id for the
 *  file read.
 */
tuple<NodeList, EdgeList, ProductList> readFile(const string& filename)
{
	// Open the input file.
    ifstream file(filename);
    if (!file.good())
    {
        cerr << "Unable to open the file '" << filename << "'." << endl;
        throw 1;
    }

	NodeList nlist;
    EdgeList elist;
    ProductList plist;
    
    unsigned int uniqueIndex = 1;

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
        Node theNewNode = {uniqueIndex};
        nlist.push_back(theNewNode);
        plist.emplace(productName, uniqueIndex);
        uniqueIndex++;
    }

    // Read all the edges in the input file.
    while (file.good())
    {
        string productName1, productName2;
        getline(file, productName1, '|');
        getline(file, productName2);
        productName1 = trimSpaces(productName1);
        productName2 = trimSpaces(productName2);

        if ((productName1.size() == 0) | (productName2.size() == 0))
            continue;
        if ((plist.find(productName1) == plist.end()) |
            (plist.find(productName2) == plist.end()))
        {
            cerr << "Wrong product name, all product names must appear before their connections are defined.\n";
            throw 1;
        }
        Edge theNewEdge = make_tuple(plist[productName1], plist[productName2], 1);
        elist.push_back(theNewEdge);
    }

    return make_tuple(nlist, elist, plist);
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
        cout << "If the option -w is used then ..." << endl; // TODO: Add helpful text.
        return 1;
    }
    bool useKargerStein = false;
    if (argc > 2 and string(argv[2]) == "-ks") useKargerStein = true; // TODO: Loop params.
    bool weightedGraph = false;
    // TODO: Read param.

    // Construct the data structure.
	NodeList nodes;
	EdgeList edges;
	ProductList products;
	tie(nodes, edges, products) = readFile(string(argv[1]));

    // Call Karger's algorithm, or its enhanced version Karger-Stein.
    unsigned int minimumCut;
    if (useKargerStein) minimumCut = Karger_Stein(nodes, edges);
    else minimumCut = Karger(nodes, edges);

    // Print results, the minimum cut and the two divisions.
	for (unsigned int i = 0; i < nodes.size(); ++i)
	{
		for (unsigned int j = 0; j < nodes[i].size(); ++j)
		{
			for (auto it = products.begin(); it != products.end(); ++it)
			{
				if (it->second == nodes[i][j])
					cout << it->first << ", ";
			}		
		}
		cout << endl;
	}
	cout << "The cut is: " << minimumCut << '\n';
}