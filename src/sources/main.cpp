#include <iostream>
#include "blockchain.h"
#include "common.h"
#include <fstream>

using namespace std;

int main()
{
    ifstream file;
    file.open("./blocks.bin");

    if (!file.is_open())
    {
        cout << "File cannot be open" << std::endl;
        return 0;
    }

    Blockchain* chain = nullptr;

    try
    {
        chain = new Blockchain(file);
    }
    catch(exception& ex)
    {
        cout << ex.what();

        if(chain)
        {
          delete chain;
        }
        file.close();
        return 1;
    }

    for(unsigned int i = 0; i < chain->nBlocks.size(); ++i)
    {
       cout << chain->nBlocks[i];
    }

    file.close();
    delete chain;

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
