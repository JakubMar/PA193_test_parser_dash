#include "block.h"
#include <string>
#include <ostream>

Block::Block(std::unique_ptr<char[]> buffer, uint32_t size) : nSize(size)
{
    binBuffer = std::move(buffer);
    uint32_t offset = 0;

    // VERSION
    if(nSize < VERSION_SIZE)
        throw InvalidBlockSizeException();
    nVersion = ParseUint32(binBuffer.get());
    offset += VERSION_SIZE;

    // HASH
    if(nSize - offset < HASH_SIZE)
        throw InvalidBlockSizeException();
    memcpy(&hashPrevBlock, binBuffer.get() + offset, HASH_SIZE);
    offset += HASH_SIZE;

    // MERKLE_ROOT
    if(nSize - offset < MERKLE_ROOT_SIZE)
        throw InvalidBlockSizeException();
    memcpy(&hashMerkleRoot, binBuffer.get() + offset, MERKLE_ROOT_SIZE);
    offset += MERKLE_ROOT_SIZE;

    // TIME
    if(nSize - offset < TIME_SIZE)
        throw InvalidBlockSizeException();
    nTime = ParseUint32(binBuffer.get() + offset);
    offset += TIME_SIZE;

    // BITS
    if(nSize - offset < BITS_SIZE)
        throw InvalidBlockSizeException();
    nBits =  ParseUint32(binBuffer.get() + offset);
    offset += BITS_SIZE;

    // NONCE
    if(nSize - offset < NONCE_SIZE)
        throw InvalidBlockSizeException();
    nNonce = ParseUint32(binBuffer.get() + offset);
    offset += NONCE_SIZE;

    headerOffsets = offsets(0,offset);

    // Transactions
    varInt countTx = ParseVarLength(binBuffer.get()+offset, nSize - offset);
    offset += countTx.second;
    size_t unread_size = nSize - offset;
    for(size_t i = 0; i < countTx.first; ++i)
    {
        nTx.emplace_back(Transaction(binBuffer.get()+offset, offset, unread_size));
    }

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
