#include "block.h"
#include <string>
#include <ostream>

Block::Block(const char* buffer, uint32_t size) : nSize(size)
{
    uint32_t offset = 0;

    nVersion = ParseUint32(buffer);
    offset += VERSION_SIZE;

    memcpy(&hashPrevBlock, buffer + offset, HASH_SIZE);
    offset += HASH_SIZE;

    memcpy(&hashMerkleRoot, buffer + offset, MERKLE_ROOT_SIZE);
    offset += MERKLE_ROOT_SIZE;

    nTime = ParseUint32(buffer + offset);
    offset += TIME_SIZE;

    nBits =  ParseUint32(buffer + offset);
    offset += BITS_SIZE;

    nNonce = ParseUint32(buffer + offset);
    offset += NONCE_SIZE;

    /*varInt countTx = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer+offset));
    offset += countTx.second;
    for(size_t i = 0; i < countTx.first; ++i)
    {
        nTx.emplace_back(Transaction(buffer, offset));
    }*/
}

std::ostream& operator<< (std::ostream& stream, const Block& block)
{
    stream << "----------BLOCK----------: " << std::endl;
    stream << "Size: " << block.nSize << std::endl;
    stream << "Version: " << block.nVersion << std::endl;
    stream << "Hash of the previous block: " << block.hashPrevBlock.GetHex() << std::endl;
    stream << "Merkle root: " << block.hashMerkleRoot.GetHex() << std::endl;
    stream << "Time: " << block.nTime << std::endl;
    stream << "Bits: " << std::hex << block.nBits << std::endl;
    stream << "Nonce: " << std::dec << block.nNonce << std::endl;
    return stream;
}
