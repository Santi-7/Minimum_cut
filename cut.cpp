#include <iostream>
#include <fstream>
#include <map>
#include <vector>

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

typedef vector<unsigned int> Node;
typedef vector<Node> NodeList;
typedef tuple<unsigned int, unsigned int> Edge;
typedef vector<Edge> EdgeList;
typedef map<string, unsigned int> ProductList;

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
        Edge theNewEdge = make_tuple(plist[productName1], plist[productName2]);
        elist.push_back(theNewEdge);
    }

    return make_tuple(nlist, elist, plist);
}

void initRandom()
{
	srand(time(NULL));
}

unsigned int getRandom(unsigned int from, unsigned int to)
{
	return rand() % (to + 1 - from) + from;
}

int main(int argc, char * argv[])
{
    // Check number of parameters.
	if (argc < 2)
    {
        cout << "Wrong number of arguments, one needed." << endl;
        cout << "Usage: " << argv[0] << " <products_file>" << endl;
        return 1;
    }

	initRandom();
	NodeList nodes;
	EdgeList edges;
	ProductList products;
	tie(nodes, edges, products) = readFile(string(argv[1]));
			
	/// Karger's algorithm.
	while(nodes.size() > 2)
	{
		unsigned int chosenEdgeIndex = getRandom(0, edges.size() - 1);
		unsigned int receivingNode = get<0>(edges[chosenEdgeIndex]);
		unsigned int absorbedNode = get<1>(edges[chosenEdgeIndex]);
		unsigned int receivingNodeIndex = 0;
		unsigned int absorbedNodeIndex = 0;
		unsigned int endEarly = 0;
		for (unsigned int i = 0; (i < nodes.size()) & (endEarly < 2); ++i)
		{
			if (nodes[i][0] == receivingNode) { receivingNodeIndex = i; endEarly++; }
			else if (nodes[i][0] == absorbedNode) { absorbedNodeIndex = i; endEarly++; }
		}
		nodes[receivingNodeIndex].insert(nodes[receivingNodeIndex].end(), nodes[absorbedNodeIndex].begin(), nodes[absorbedNodeIndex].end());
		nodes.erase(nodes.begin() + absorbedNodeIndex);
		edges.erase(edges.begin() + chosenEdgeIndex);
		
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
	
	for (unsigned int i = 0; i < nodes.size(); ++i)
	{
		for (unsigned int j = 0; j < nodes[i].size(); ++j)
			cout << nodes[i][j] << ", ";
		cout << endl;
	}
	cout << "The cut is: " << edges.size() << '\n';
}