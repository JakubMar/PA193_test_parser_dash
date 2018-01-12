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
    /**
     * @brief nBlocks vector of blocks
     */
    std::vector<Block> nBlocks;
    /**
     * @brief srcFile file to read blockchain from
     */
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
     * @throws ReadFileException
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
    /**
     * @brief readMagicNumber reads and checks magic number of block
     * @param file source of data
     * @throws ReadFileException
     * @throws MagicNumberException
     */
    void readMagicNumber(std::ifstream& file);

    /**
     * @brief readBlockSize reads and chceks the size of block
     * @param file source of data
     * @throws ReadFileException
     * @throws InvalidBlockSizeException
     * @return block size
     */
    uint32_t readBlockSize(std::ifstream& file);

    /**
     * @brief readBlockContent tries to read block_size of bytes from file
     * @param file source of data
     * @param block_size size to read
     * @throws ReadFileException
     * @return unique pointer to read data
     */
    std::unique_ptr<char[]> readBlockContent(std::ifstream& file, uint32_t block_size);

    /**
     * @brief Block Constructor for testing
     */
    Blockchain() {}

};
