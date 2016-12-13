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
#include <assert.h>

using namespace std;

/**
 * Removes the spaces before and after a string.
 * @author StackOverflow user: @elxala from
 *      http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring#217605
 *
 * @param str Input string from which spaces will be removed.
 * @return string without leading or treading spaces.
 */
std::string& TrimSpaces(std::string &str)
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
        bool emplacedCorrectly = get<1>(productMap.emplace(productName, Product(productName)));
        if (!emplacedCorrectly) { cerr << "Error inserting product in the map.\n"; return 1; }
        kargerGraph.AddProduct(&productMap[productName]);
    }

    // Read all the edges in the input file.
    while (file.good())
    {
        string productName1, productName2;
        getline(file, productName1, '|');
        getline(file, productName2);
        productName1 = TrimSpaces(productName1);
        productName2 = TrimSpaces(productName2);

        if ((productName1.size() == 0) | (productName2.size() == 0))
            continue;
        if ((productMap.find(productName1) == productMap.end()) |
            (productMap.find(productName2) == productMap.end()))
        {
            cerr << "Wrong product name, all product names must appear before their connections are defined.\n";
            return 1;
        }
        Edge tmpEdge(productMap[productName1].GetPack(), productMap[productName2].GetPack());
        kargerGraph.AddEdge(tmpEdge);
    }

    // Karger's algorithm. Contract a random edge until only two vertices exist.
    unsigned long vertices = productMap.size();
    while (vertices --> 2) kargerGraph.FuseStep();

    // Show results.
    cout << "The min cut is " << kargerGraph.GetEdges().size() << ".\n\n";
    for (ProductsPack pack : kargerGraph.GetPacks()) pack.Print();
}