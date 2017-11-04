#pragma once

#include <cmath>
#include "common.h"
#include "transaction.h"

class Block
{
public:

    Block(std::unique_ptr<char[]> buffer, uint32_t size);

    int32_t getVersion() const;
    uint256 getHashPrevBlock() const;
    uint256 getHashMerkleRoot() const;
    uint32_t getTime() const;
    uint32_t getBits() const;
    uint32_t getNonce() const;
    uint32_t getSize() const;
    std::vector<Transaction> getTx() const;
    char* getBinBufferData() const;

    friend class TestHelper;
    friend std::ostream& operator<< (std::ostream& stream, const Block& block_);
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

    validStat isValid{true, "unknown reason"};

    Block() {}
};

