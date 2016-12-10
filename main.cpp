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
        // If the line is empty skip it
        if (productName.size() == 0)
        {
            numberOfProducts++; continue;
        }
        // TODO: Check that the pointer in the graph points to the map
        auto productInMap = productMap.emplace(productName, Product(productName));
        kargerGraph.AddProduct(make_shared<Product>(get<1>(*get<0>(productInMap))));
    }

    // Read all the edges in the input file.
    while (file.good())
    {
        string product1, product2;
        getline(file, product1, '|');
        // If the line is empty skip it.
        if (product1.size() == 0)
        {
            numberOfProducts++; continue;
        }
        getline(file, product2);
    }

    // Karger's algorithm. Contract a random edge until only two vertices exist.
    unsigned long step = productMap.size();
    while (step --> 2) kargerGraph.FuseStep();

    // TODO: mPacks in kargerGraph will have the two desired packs. Show them.
    // TODO: mEdges.size() will mean the min cut.
}