#include <iostream>
#include "blockchain.h"
#include "validator.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 2) return 1;

    //std::string fileName = "./two_blocks.txt";

    try
    {
        //        Blockchain chain(argv[1]);
        //        const std::vector<Block> &blocks = chain.getBlocks();

        //        unsigned int i = 0;
        //        bool notEnd;
        //        do
        //        {
        //            notEnd = chain.parseFile();
        //            for(; i < blocks.size(); ++i)
        //            {
        //               cout << std::endl << blocks[i];
        //            }
        //            i = 1;
        //        } while(notEnd);

//        std::unique_ptr<Blockchain> chain(new Blockchain(argv[1]));
//        const std::vector<Block> &blocks = chain.get()->getBlocks();
//        unsigned int i = 0;
//        bool notEnd;
//        do
//        {
//            notEnd = chain->parseFile();
//            for(; i < blocks.size(); ++i)
//            {
//                cout << std::endl << blocks[i];
//            }
//            i = 1;
//        } while(notEnd);

                Blockchain chain(argv[1]);
                 Validator val;
                val.validateBlockChain(chain);

                unsigned int i = 0;
                bool notEnd;
                do
                {
                    notEnd = chain.parseFile();
                    for(; i < chain.getBlocks().size(); ++i)
                    {
                       cout << std::endl << chain.getBlocks()[i];
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
