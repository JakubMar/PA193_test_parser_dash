#include <iostream>
#include "blockchain.h"
#include <fstream>

using namespace std;



int main()
{
    std::cout << "Starting main" << std::endl;
    std::unique_ptr<Blockchain> chain;

    try
    {
        std::string fileName = "./blocks.bin";
        std::unique_ptr<Blockchain> tmpChain(new Blockchain(fileName));
        tmpChain->parseFile();
        chain = std::move(tmpChain);
    }
    catch(ParserException& ex)
    {
        cout << ex.what() << endl;
        return 1;
    }

    for(unsigned int i = 0; i < chain->getBlocks().size(); ++i)
    {
       cout << chain->getBlocks()[i];
    }

    return 0;
}
