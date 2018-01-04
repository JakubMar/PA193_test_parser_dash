#include "blockchain.h"
#include <iostream>

Blockchain::Blockchain(std::string fileName)
{
    srcFile.open(fileName.c_str());

    if (!srcFile.is_open())
    {
        throw ReadFileException("Failed to open file");
    }
}

const std::vector<Block>& Blockchain::getBlocks() const
{
    return nBlocks;
}

bool Blockchain::parseFile()
{
    unsigned int numberOfBlocks = 0;
    if (nBlocks.size() > 1)
    {
        nBlocks.erase(nBlocks.begin(), nBlocks.end() - 1);
    }

    while (numberOfBlocks < MAX_NUMBER_OF_BLOCKS && !srcFile.eof())
    {
        readMagicNumber(srcFile);

        if (srcFile.eof())
        {
            return false;
        }

        uint32_t block_size = readBlockSize(srcFile);
        std::unique_ptr<char[]> block_buffer = readBlockContent(srcFile, block_size);

        nBlocks.push_back(Block(std::move(block_buffer), block_size));

        ++numberOfBlocks;
    }
    return !srcFile.eof();
}

void Blockchain::readMagicNumber(std::ifstream& file)
{
    const unsigned bufferSize = MAGIC_NUMBER_SIZE;
    char buffer[bufferSize];
    file.read(buffer, bufferSize);

    if (file.fail())
    {
        if (file.eof() && file.gcount() == 0)
        {
            return;
        }

        throw ReadFileException("Reading magic number from the file was not succesfull");
    }

    if (memcmp(buffer, MAGIC_NUMBER, bufferSize) != 0)
    {
        throw MagicNumberException();
    }
}


uint32_t Blockchain::readBlockSize(std::ifstream& file)
{
    uint32_t block_size;
    file.read(reinterpret_cast<char*>(&block_size), BLOCK_SIZE_SIZE);

    if (file.fail())
    {
        throw ReadFileException("Reading size of the block from the file was not succesfull");
    }

    if (block_size > MAX_BLOCKFILE_SIZE || block_size < BLOCK_HEADER_SIZE)
    {
        throw InvalidBlockSizeException();
    }


    return block_size;
}


std::unique_ptr<char[]> Blockchain::readBlockContent(std::ifstream& file, uint32_t block_size)
{
    std::unique_ptr<char[]> block_buffer(new char[block_size]);
    file.read(block_buffer.get(), block_size);

    if (file.fail())
    {
        throw ReadFileException("Reading content of block from file was not succesfull");
    }

    return block_buffer;
}
