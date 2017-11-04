#include "block.h"
#include <ctime>
#include <string>
#include <ostream>

Block::Block(std::unique_ptr<char[]> buffer, uint32_t size) : size(size)
{
    binBuffer = std::move(buffer);
    uint32_t offset = 0;

    // VERSION
    if(size < VERSION_SIZE)
        throw InvalidBlockSizeException();
    version = ParseUint32(binBuffer.get());
    offset += VERSION_SIZE;

    // HASH
    if(size - offset < HASH_SIZE)
        throw InvalidBlockSizeException();
    memcpy(&hashPrevBlock, binBuffer.get() + offset, HASH_SIZE);
    offset += HASH_SIZE;

    // MERKLE_ROOT
    if(size - offset < MERKLE_ROOT_SIZE)
        throw InvalidBlockSizeException();
    memcpy(&hashMerkleRoot, binBuffer.get() + offset, MERKLE_ROOT_SIZE);
    offset += MERKLE_ROOT_SIZE;

    // TIME
    if(size - offset < TIME_SIZE)
        throw InvalidBlockSizeException();
    time = ParseUint32(binBuffer.get() + offset);
    offset += TIME_SIZE;

    // BITS
    if(size - offset < BITS_SIZE)
        throw InvalidBlockSizeException();
    bits =  ParseUint32(binBuffer.get() + offset);
    offset += BITS_SIZE;

    // NONCE
    if(size - offset < NONCE_SIZE)
        throw InvalidBlockSizeException();
    nonce = ParseUint32(binBuffer.get() + offset);
    offset += NONCE_SIZE;

    headerOffsets = offsets(0,offset);

    // Transactions
    varInt countTx = ParseVarLength(binBuffer.get()+offset, size - offset);
    offset += countTx.second;
    size_t unread_size = size - offset;
    for(size_t i = 0; i < countTx.first; ++i)
    {
        tx.emplace_back(Transaction(binBuffer.get()+offset, offset, unread_size));
    }

}

int32_t Block::getVersion() const
{
    return version;
}

uint256 Block::getHashPrevBlock() const
{
    return hashPrevBlock;
}

uint256 Block::getHashMerkleRoot() const
{
    return hashMerkleRoot;
}

uint32_t Block::getTime() const
{
    return time;
}

uint32_t Block::getBits() const
{
    return bits;
}

uint32_t Block::getNonce() const
{
    return nonce;
}

uint32_t Block::getSize() const
{
    return size;
}

std::vector<Transaction> Block::getTx() const
{
    return tx;
}

char* Block::getBinBufferData() const
{
    return binBuffer.get();
}

validStat& Block::getValidStat() const
{
    return isValid;
}

std::ostream& operator<< (std::ostream& stream, const Block& block)
{
    stream << "----------BLOCK----------: " << std::endl;
    if(block.isValid.first)
    {
        stream << "Size: " << block.size << std::endl;
        stream << "Version: " << block.version << std::endl;
        stream << "Prev block hash: " << block.hashPrevBlock.GetHex() << std::endl;
        stream << "Merkle root: " << block.hashMerkleRoot.GetHex() << std::endl;
        std::time_t time = block.time;
        stream << "Time: " << std::asctime(std::localtime(&time));
        stream << "Bits: " << std::hex << block.bits << std::endl;
        stream << "Nonce: " << std::dec << block.nonce << std::endl;
        for(auto& it : block.tx)
        {
            stream << it << std::endl;
        }
    }
    else
    {
        stream << "Block is not valid: " << block.isValid.second << std::endl;
    }
    return stream;
}
