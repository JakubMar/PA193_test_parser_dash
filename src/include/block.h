#pragma once

#include <cmath>
#include "common.h"
#include "transaction.h"

class Block
{
public:

    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;
    uint32_t nSize;
    std::vector<Transaction> nTx;

    offsets headerOffsets;
    std::unique_ptr<char[]> binBuffer;

    Block(std::unique_ptr<char[]> buffer, uint32_t size);
    friend class TestHelper;
    friend std::ostream& operator<< (std::ostream& stream, const Block& block_);
private:
    /*
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;
    uint32_t nSize;
    std::vector<Transaction> nTx;
    offsets headerOffsets;
    std::unique_ptr<char[]> binBuffer;
    */
    validStat isValid{true, "unknown reason"};

    Block() {}
};

