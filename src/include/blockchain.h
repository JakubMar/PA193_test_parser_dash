#pragma once

#include <vector>
#include <block.h>
#include <fstream>
#include <stdexcept>

const uint32_t MAGIC_NUMBER_SIZE = 4;
const uint32_t BLOCK_SIZE_SIZE = 4;

class Blockchain
{

private:

    std::vector<Block> nBlocks;
    std::ifstream srcFile;

private:
    
    void ReadMagicNumber(std::ifstream& file);

    uint32_t ReadBlockSize(std::ifstream& file);

    std::unique_ptr<char[]> ReadBlockContent(std::ifstream& file, uint32_t block_size);

public:
    
    const std::vector<Block> &getBlocks();
    
    Blockchain(std::string fileName);

    void parseFile();
    
};
