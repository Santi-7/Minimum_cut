/** ---------------------------------------------------------------------------
 ** main.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <KargerGraph.hpp>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // Check number of parameters.
    if (argc != 2)
    {
        cerr << "Incorrect number of parameters, expected 1, received " << argc-1 << ".\n";
        cerr << "Use: $" << argv[0] << " <file>" << endl;
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