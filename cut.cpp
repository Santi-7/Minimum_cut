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
#include <unordered_map>

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
tuple<unordered_map<string, Product>, KargerGraph> readFile(const string& filename, const bool readWeightedGraph, RandomNumberEngine &rng)
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
	KargerGraph kargerGraph(readWeightedGraph, rng);

    unsigned int numberOfProducts;
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
        bool emplacedCorrectly = get<1>(productMap.emplace(productName, Product(productName, numberOfProducts)));
        if (!emplacedCorrectly) { cerr << "Error inserting product in the map.\n"; throw 1; }
        kargerGraph.AddProduct(&productMap[productName]);
    }

    string weight;
    // Read all the edges and weights in the input file.
    while (file.good())
    {
        // Read.
        string productName1, productName2;
        getline(file, productName1, '|');
        if (readWeightedGraph)
        {
            getline(file, productName2, '|');
            getline(file, weight);
        }
        else
        {
            getline(file, productName2);
        }
        // Get nodes of the edge.
        productName1 = trimSpaces(productName1);
        productName2 = trimSpaces(productName2);
        if ((productName1.size() == 0) | (productName2.size() == 0))
            continue;
        if ((productMap.find(productName1) == productMap.end()) |
            (productMap.find(productName2) == productMap.end()))
        {
            cerr << "Wrong product name, all product names must appear before their connections are defined.\n";
            throw 1;
        }
        // Insert edge.
        Edge theNewEdge;
        if (readWeightedGraph)
        {
            try
            {

            theNewEdge = Edge(productMap[productName1].GetId(),
                              productMap[productName2].GetId(),
                              static_cast<unsigned int>(stoi(weight)));

            } catch(invalid_argument)
            {
                cerr << "Wrong edge weight, expected an integer\n";
                throw 1;
            }

        }
        else
        {
            theNewEdge = Edge(productMap[productName1].GetId(),
                              productMap[productName2].GetId());
        }
        kargerGraph.AddEdge(theNewEdge);
    }

    return make_tuple(productMap, kargerGraph);
}

/**
 * Read file from parameters and run Karger's algorithm on the graph described in it.
 */
int main(int argc, char * argv[])
{
    Engine randomEngine = MERSENNE;
    // Check number of parameters.
	if (argc < 2)
    {
        cout << "Wrong number of arguments, at least one needed." << endl;
        cout << "Usage: " << argv[0] << " <products_file> [-ks] [-w]" << endl;
        cout << "If the option -ks is used then the algorithm run will be Karger-Stein's." << endl;
        cout << "If the option -w is used then the product file will be treated as a weighted graph." << endl;
        cout << "If the option -rand=C is used then the random number generator used will be C rand()." << endl;
        cout << "If the option -rand=MERSENNE is used then the random number generator used will be a C++ Mersenne twister." << endl;
        return 1;
    }
    bool useKargerStein = false;
    bool weightedGraph = false;
    for (int i = 2; i < argc; ++i)
    {
	    string tmpArg = string(argv[i]);
	    if (tmpArg == "-ks") useKargerStein = true;
	    else if (tmpArg == "-w") weightedGraph = true;
        else if (tmpArg == "-rand=C") randomEngine = CLASSIC_C;
        else if (tmpArg == "-rand=MERSENNE") randomEngine = MERSENNE;
        else
        {
            cerr << "Unrecognized parameter: '" << tmpArg << "'\n";
            return 1;
        }
    }

    // Construct the data structure.
    unordered_map<string, Product> productMap;
    KargerGraph kargerGraph;
    RandomNumberEngine rng(randomEngine);
	tie(productMap, kargerGraph) = readFile(string(argv[1]), weightedGraph, rng);

    // Call Karger's algorithm, or its enhanced version Karger-Stein.
    unsigned int minimumCut;
    if (useKargerStein) minimumCut = kargerGraph.KargerSteinAlgorithm();
    else minimumCut = kargerGraph.KargerAlgorithm();

    // Show results.
    cout << "The min cut is " << minimumCut << ".\n\n";
    for (pair<unsigned int, ProductsPack> pack : kargerGraph.GetPacks())
    {
        cout << "Pack: ";
        for (unsigned int product : pack.second.mProducts)
        {
            for (auto it = productMap.begin(); it != productMap.end(); ++it)
            {
                if (it->second.GetId() == product) {
                    cout << it->first << ", ";
                    break;
                }
            }
        }
        cout << endl;
    }
}