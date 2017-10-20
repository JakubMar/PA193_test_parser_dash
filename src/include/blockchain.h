#ifndef BLOCKCHAIN
#define BLOCKCHAIN

#include <vector>
#include <block.h>
#include <fstream>
#include <stdexcept>

const uint32_t MAGIC_NUMBER_SIZE = 4;
const uint32_t BLOCK_SIZE_SIZE = 4;

class Blockchain
{

    std::vector<Block> nBlocks;


    void ReadMagicNumber(std::ifstream& file)
    {

        unsigned bufferSize = MAGIC_NUMBER_SIZE;
        char buffer[bufferSize];
        file.read(buffer, bufferSize);

        if(file.eof())
        {
            std::cout << "All blocks were succesfuly parsed" << std::endl;
            return;
        }

        if(file.fail())
        {
            throw std::runtime_error("Reading magic number from file was not succesfull");
        }

        if(memcmp(buffer, MAGIC_NUMBER, bufferSize) != 0)
        {
            //printf("%hhX %hhX %hhX %hhX\n", buffer[0], buffer[1], buffer[2], buffer[3]); -- for debug
            throw std::runtime_error("File does not start with magic number");
        }

        //printf("%hhX %hhX %hhX %hhX\n", buffer[0], buffer[1], buffer[2], buffer[3]); -- for debug
        std::cout << "Magic word found, parsing another block" << std::endl;
    }


    uint32_t ReadBlockSize(std::ifstream& file)
    {
        uint32_t block_size;
        file.read(reinterpret_cast<char*>(&block_size), BLOCK_SIZE_SIZE);

        if(file.fail())
        {
            throw std::runtime_error("Reading size of block from file was not succesfull");
        }

        if(block_size > MAX_BLOCKFILE_SIZE)
        {
            throw std::runtime_error("Block size is invalid");
        }

        std::cout << "Block size: " << block_size  << std::endl;

        return block_size;
    }
//TODO: this is allocating memory? kinda magic - maybe use move semantics instead?
    char* ReadBlockContent(std::ifstream& file, uint32_t block_size)
    {
        char* block_buffer = new char[block_size];
        file.read(block_buffer, block_size);

        if(file.fail())
        {
            throw std::runtime_error("Reading content of block from file was not succesfull");
        }

        return block_buffer;
    }


    void initializer(std::ifstream& file){
        unsigned int numberOfBlocks = 0;

        while(numberOfBlocks < MAX_NUMBER_OF_BLOCKS && !file.eof())
        {
            ReadMagicNumber(file);

            if(file.eof())
            {
                break;
            }

            uint32_t block_size = ReadBlockSize(file);
            char* block_buffer = ReadBlockContent(file, block_size);

            nBlocks.push_back(Block(block_buffer, block_size));

            delete[] block_buffer;

            ++numberOfBlocks;
        }
    }

public:

    const std::vector<Block> &getBlocks(){
        return nBlocks;
    }

    Blockchain(std::ifstream& file)
    {
        initializer(file);
    }

    Blockchain(std::string fileName){
        std::ifstream file;
        file.open(fileName.c_str());

        if (!file.is_open())
        {
            throw std::runtime_error("File cannot be open");
        }

        initializer(file);
    }

};

#endif // BLOCKCHAIN

