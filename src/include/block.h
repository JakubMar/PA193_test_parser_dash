#pragma once

#include <cmath>
#include "common.h"
#include "transaction.h"

class Block
{
public:

    /**
     * @brief Block
     * @param buffer
     * @param size
     */
    Block(std::unique_ptr<char[]> buffer, uint32_t size);

    /**
     * @brief getVersion
     * @return
     */
    int32_t getVersion() const;

    /**
     * @brief getHashPrevBlock
     * @return
     */
    uint256 getHashPrevBlock() const;

    /**
     * @brief getHashMerkleRoot
     * @return
     */
    uint256 getHashMerkleRoot() const;

    /**
     * @brief getTime
     * @return
     */
    uint32_t getTime() const;

    /**
     * @brief getBits
     * @return
     */
    uint32_t getBits() const;

    /**
     * @brief getNonce
     * @return
     */
    uint32_t getNonce() const;

    /**
     * @brief getSize
     * @return
     */
    uint32_t getSize() const;

    /**
     * @brief getTx
     * @return
     */
    std::vector<Transaction> getTx() const;

    /**
     * @brief getBinBufferData
     * @return
     */
    char* getBinBufferData() const;

    /**
     * @brief getValidStat
     * @return
     */
    validStat& getValidStat() const;

    /**
     *
     */
    friend class TestHelper;

    /**
     * @brief operator <<
     * @param stream
     * @param block_
     * @return
     */
    friend std::ostream& operator<< (std::ostream& stream, const Block& block_);

    /**
     *
     */
    friend class Validator;


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

    Block() {}
};

