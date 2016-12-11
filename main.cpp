/** ---------------------------------------------------------------------------
 ** main.cpp
 ** TODO: Add doc.
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
std::string& TrimSpaces (std::string & str)
{
    // right trim
    while (str.length () > 0 && (str [str.length ()-1] == ' ' || str [str.length ()-1] == '\t'))
        str.erase (str.length ()-1, 1);

    // left trim
    while (str.length () > 0 && (str [0] == ' ' || str [0] == '\t'))
        str.erase (0, 1);
    return str;
}

int main(int argc, char *argv[])
{
    // Check the number of parameters.
    if (argc != 2)
    {
        cerr << "Incorrect number of parameters, expected 1, received " << argc-1 << ".\n";
        cerr << "Usage: $> " << argv[0] << " <file>" << endl;
        return 1;
    }

    // Open the input file.
    ifstream file(argv[1]);
    if (!file.good())
    {
        cerr << "Unable to open the file '" << argv[1] << "'." << endl;
        return 1;
    }

    // Karger's Graph.
    KargerGraph kargerGraph;
    unordered_map<string, Product> productMap;

    int numberOfProducts;
    file >> numberOfProducts;
    // Read all the products in the input file.
    while (numberOfProducts --> 0)
    {
        string productName;
        getline(file, productName);
        productName = TrimSpaces(productName);
        // If the line is empty skip it
        if (productName.size() == 0)
        {
            numberOfProducts++; continue;
        }
        // TODO: Check that the pointer in the graph points to the map
        auto productInMap = productMap.emplace(productName, Product(productName));
        kargerGraph.AddProduct(shared_ptr<Product>(&get<1>(*get<0>(productInMap))));
    }

    // Read all the edges in the input file.
    while (file.good())
    {
        string productName1, productName2;
        getline(file, productName1, '|');
        getline(file, productName2);
        productName1 = TrimSpaces(productName1);
        productName2 = TrimSpaces(productName2);

        if (productName1.size() == 0 || productName2.size() == 0)
        {
            continue;
        }

        Edge tmpEdge(productMap[productName1].GetPack(), productMap[productName2].GetPack());
        kargerGraph.AddEdge(tmpEdge);
    }

    // Karger's algorithm. Contract a random edge until only two vertices exist.
    unsigned long step = productMap.size();
    while (step --> 2)
    {
        kargerGraph.FuseStep();
    }

    //cout << kargerGraph.mEdges.size() << '\n';
    // TODO: mPacks in kargerGraph will have the two desired packs. Show them.
    // TODO: mEdges.size() will mean the min cut.
}