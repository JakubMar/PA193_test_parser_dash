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

    offsets beginEndOffsets;
    std::unique_ptr<char[]> binBuffer;

    Block(std::unique_ptr<char[]> buffer, uint32_t size);
};

std::ostream& operator<< (std::ostream& stream, const Block& block);
