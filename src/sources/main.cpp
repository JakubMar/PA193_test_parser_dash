#include <iostream>
#include "blockchain.h"
#include "validator.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Argument missing: path to file containing blockchain" << std::endl;
        return 1;
    }

    try
    {
        Blockchain chain(argv[1]);
        chain.parseFile();
        Validator::validateBlockChain(chain);
        for (auto& it : chain.getBlocks())
        {
            cout << it << std::endl;
        }
    }
    catch (ParserException& ex)
    {
        cerr << ex.what() << endl;
        return 1;
    }

    return 0;
}
