#pragma once

#include <block.h>
#include <fstream>
#include <stdexcept>


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
    
    const std::vector<Block> &getBlocks() const;
    
    Blockchain(std::string fileName);

    bool parseFile();
    
};
