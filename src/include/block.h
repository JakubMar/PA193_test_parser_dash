#pragma once

#include <cmath>
#include "common.h"
#include "transaction.h"

/**
 * @brief The Block class data structure for holding transactions
 */
class Block
{
private:
    int32_t version;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t time;
    uint32_t bits;
    uint32_t nonce;
    uint32_t size;
    std::vector<Transaction> tx;
    offsets headerOffsets;
    std::unique_ptr<char[]> binBuffer;
    mutable validStat isValid{false, "unknown reason"};

public:

    /**
     * @brief Block Constructor of data holding structure
     * @param buffer memory to parse to corrsponding values
     * @param size size of the buffer
     */
    Block(std::unique_ptr<char[]> buffer, uint32_t size);

    /**
     * @brief getVersion getter for private member: version
     * @return version
     */
    int32_t getVersion() const;

    /**
     * @brief getHashPrevBlock getter for private member: hash of previous block
     * @return hashPrevBlock
     */
    uint256 getHashPrevBlock() const;

    /**
     * @brief getHashMerkleRoot getter for private member: merkle root hash
     * @return hashMerkleRoot
     */
    uint256 getHashMerkleRoot() const;

    /**
     * @brief getTime getter for private member: time
     * @return time
     */
    uint32_t getTime() const;

    /**
     * @brief getBits getter for private member: bits
     * @return bits
     */
    uint32_t getBits() const;

    /**
     * @brief getNonce getter for private member: nonce
     * @return nonce
     */
    uint32_t getNonce() const;

    /**
     * @brief getSize getter for private member: size
     * @return size
     */
    uint32_t getSize() const;

    /**
     * @brief getTx getter for private member: vector of transactions
     * @return vector of transactions
     */
    std::vector<Transaction> getTx() const;

    /**
     * @brief getBinBufferData getter for private member: binary data of block
     * @return binBuffer
     */
    char* getBinBufferData() const;

    /**
     * @brief getValidStat getter for private member: isValid attribute
     * @return isValid
     */
    validStat& getValidStat() const;

    /**
     * @brief friend class for validating the block
     */
    friend class Validator;

    /**
     * @brief friend class for testing
     */
    friend class TestHelper;

    /**
     * @brief operator << overloaded operator for printing the data
     * @param stream stream to write
     * @param block_ block to print
     * @return stream
     */
    friend std::ostream& operator<< (std::ostream& stream, const Block& block_);

private:
    Block() {}
};

