#include "blockchain.h"
#include <iostream>

Blockchain::Blockchain(std::string fileName)
{
    srcFile.open(fileName.c_str());

    if (!srcFile.is_open())
    {
        throw std::runtime_error("Failed to open file\n");
    }
}

const std::vector<Block>& Blockchain::getBlocks()
{
    return nBlocks;
}

void Blockchain::parseFile()
{
    unsigned int numberOfBlocks = 0;

    while(numberOfBlocks < MAX_NUMBER_OF_BLOCKS && !srcFile.eof())
    {
        ReadMagicNumber(srcFile);

        if(srcFile.eof())
        {
            break;
        }

        uint32_t block_size = ReadBlockSize(srcFile);
        std::unique_ptr<char[]> block_buffer= ReadBlockContent(srcFile, block_size);

        nBlocks.push_back(Block(block_buffer.get(), block_size));

        ++numberOfBlocks;
    }
}

void Blockchain::ReadMagicNumber(std::ifstream& file)
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
        throw std::runtime_error("File does not start with magic number");
    }

    std::cout << "Magic word found, parsing another block" << std::endl;
}


uint32_t Blockchain::ReadBlockSize(std::ifstream& file)
{
    uint32_t block_size;
    file.read(reinterpret_cast<char*>(&block_size), BLOCK_SIZE_SIZE);

    if(file.fail())
    {
        throw std::runtime_error("Reading size of block from file was not succesfull");
    }

    if(block_size > MAX_BLOCKFILE_SIZE || block_size < 80)
    {
        throw std::runtime_error("Block size is invalid");
    }

    std::cout << "Block size: " << block_size  << std::endl;

    return block_size;
}


std::unique_ptr<char[]> Blockchain::ReadBlockContent(std::ifstream& file, uint32_t block_size)
{
    std::unique_ptr<char[]> block_buffer(new char[block_size]);
    file.read(block_buffer.get(), block_size);

    if(file.fail())
    {
        throw std::runtime_error("Reading content of block from file was not succesfull");
    }

    return block_buffer;
}
