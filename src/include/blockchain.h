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
    
    void readMagicNumber(std::ifstream& file);

    uint32_t readBlockSize(std::ifstream& file);

    std::unique_ptr<char[]> readBlockContent(std::ifstream& file, uint32_t block_size);

    Blockchain() {}

public:
    
    /**
     * @brief getBlocks
     * @return
     */
    const std::vector<Block> &getBlocks() const;
    
    /**
     * @brief Blockchain
     * @param fileName
     */
    Blockchain(std::string fileName);

    /**
     * @brief parseFile
     * @return
     */
    bool parseFile();

    /**
     *
     */
    friend class TestHelper;
    
};
