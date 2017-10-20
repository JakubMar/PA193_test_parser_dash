#include <iostream>
#include "blockchain.h"
#include "common.h"
#include <fstream>
#include <memory>

using namespace std;

int main()
{
    std::cout << "Starting main" << std::endl;
    std::unique_ptr<Blockchain> chain;

    try
    {
        std::string fileName = "./blocks.bin";
        std::unique_ptr<Blockchain> tmpChain(new Blockchain(fileName));
        chain = std::move(tmpChain);
    }
    catch(exception& ex)
    {
        cout << ex.what();
        return 1;
    }

    for(unsigned int i = 0; i < chain->getBlocks().size(); ++i)
    {
       cout << chain->getBlocks()[i];
    }

    return 0;
}

/*
char buffer[] = {0x00,0x11};

buffer = read_resources();
block = parse(buffer);
if(block)
{
if(valid(block))
    {
     print(block);
    }
}
*/
