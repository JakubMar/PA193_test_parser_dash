#pragma once

#include <block.h>
#include <fstream>
#include <stdexcept>

/**
 * @brief The Blockchain class represents whole blockchain
 */
class Blockchain
{
private:
    std::vector<Block> nBlocks;
    std::ifstream srcFile;

public:
    
    /**
     * @brief getBlocks getter for private member: vector of blocks
     * @return nBlocks
     */
    const std::vector<Block> &getBlocks() const;
    
    /**
     * @brief Blockchain Constructor opens file or throws exception
     * @param fileName file to open
     */
    Blockchain(std::string fileName);

    /**
     * @brief parseFile reads srcFile and cuts data to blocks
     * syntax validation, throws exceptions if invalid blocks occurs
     * @return true if syntax validation of blockchain is successful
     */
    bool parseFile();

    /**
     * @brief friend class for testing
     */
    friend class TestHelper;

private:

    void readMagicNumber(std::ifstream& file);
    uint32_t readBlockSize(std::ifstream& file);
    std::unique_ptr<char[]> readBlockContent(std::ifstream& file, uint32_t block_size);
    Blockchain() {}
    
};
