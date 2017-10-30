#include <iostream>
#include "blockchain.h"
#include "validator.h"
#include <fstream>

using namespace std;

int main()
{

    std::string fileName = "./two_blocks.bin";

    try
    {
        std::unique_ptr<Blockchain> chain(new Blockchain(fileName));
        unsigned int i = 0;
        bool notEnd;
        do
        {
            notEnd = chain->parseFile();
            for(i; i < chain->getBlocks().size(); ++i)
            {
               cout << std::endl << chain->getBlocks()[i];
            }
            i = 1;
        } while(notEnd);
    }
    catch(ParserException& ex)
    {
        cout << ex.what() << endl;
        return 1;
    }



    return 0;
}
