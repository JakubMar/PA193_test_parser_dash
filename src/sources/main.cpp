#include <iostream>
#include "blockchain.h"
#include "common.h"
#include <fstream>
#include <memory>

using namespace std;

int main()
{
    std::cout << "Starting main" << std::endl;
    ifstream file;
    file.open("./blocks.bin");

    if (!file.is_open())
    {
        cout << "File cannot be open" << std::endl;
        return 0;
    }

    std::unique_ptr<Blockchain> chain;

    try
    {
        std::unique_ptr<Blockchain> tmpChain(new Blockchain(file));
        chain = std::move(tmpChain);
    }
    catch(exception& ex)
    {
        cout << ex.what();
        return 1;
    }

    for(unsigned int i = 0; i < chain->nBlocks.size(); ++i)
    {
       cout << chain->nBlocks[i];
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
