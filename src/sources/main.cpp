#include <iostream>
#include "blockchain.h"
#include "validator.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 2) return 1;

    //std::string fileName = "./two_blocks.txt";
    //std::string fileName = "/home/xvancik/Desktop/PA193_test_parser_dash/blockchainBigTest.bin";

    try
    {
        Blockchain chain(argv[1]);

        chain.parseFile();
        Validator::validateBlockChain(chain);
        for(int i = 0; i < chain.getBlocks().size(); ++i)
        {
            cout << std::endl << chain.getBlocks()[i];
        }
    }
    catch(ParserException& ex)
    {
        cout << ex.what() << endl;
        return 1;
    }

    return 0;
}
