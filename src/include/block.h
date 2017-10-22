#pragma once

#include <cmath>
#include "common.h"
#include "transaction.h"

const uint32_t VERSION_SIZE = 4;
const uint32_t HASH_SIZE = 32;
const uint32_t MERKLE_ROOT_SIZE = 32;
const uint32_t TIME_SIZE = 4;
const uint32_t BITS_SIZE = 4;
const uint32_t NONCE_SIZE = 4;
const uint32_t BLOCK_HEADER_SIZE = VERSION_SIZE + HASH_SIZE + MERKLE_ROOT_SIZE + TIME_SIZE + BITS_SIZE + NONCE_SIZE;

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

    Block(const char* buffer, uint32_t size);
};

std::ostream& operator<< (std::ostream& stream, const Block& block);
