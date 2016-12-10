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
    if (!file.is_open())
    {
        cerr << "Unable to open the file '" << argv[1] << "'." << endl;
        return 1;
    }

    // Karger's Graph.
    KargerGraph kargerGraph();

    //
    // TODO: Read products and edges from file.
    /* TODO: Construct a hash table with all the products.
     * TODO:           a Kargers' Graph
     */
    // TODO: Karger's algorithm.
}