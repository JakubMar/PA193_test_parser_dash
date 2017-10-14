#ifndef BLOCK
#define BLOCK

#include "common.h"
#include <cmath>

// This probably works only for bitcoin
/*inline float fast_log(float val)
{
   int * const exp_ptr = reinterpret_cast <int *>(&val);
   int x = *exp_ptr;
   const int log_2 = ((x >> 23) & 255) - 128;
   x &= ~(255 << 23);
   x += 127 << 23;
   *exp_ptr = x;

   val = ((-1.0f/3) * val + 2) * val - 2.0f/3;
   return ((val + log_2) * 0.69314718f);
}

float difficulty(unsigned int bits)
{
    static double max_body = fast_log(0x00ffff), scaland = fast_log(256);
    return exp(max_body - fast_log(bits & 0x00ffffff) + scaland * (0x1d - ((bits & 0xff000000) >> 24)));
}*/

const uint32_t VERSION_SIZE = 4;
const uint32_t HASH_SIZE = 32;
const uint32_t MERKLE_ROOT_SIZE = 32;
const uint32_t TIME_SIZE = 4;
const uint32_t BITS_SIZE = 4;
const uint32_t NONCE_SIZE = 4;

class Block
{
public:

    int32_t nVersion;
    QByteArray hashPrevBlock;
    QByteArray hashMerkleRoot;
    uint32_t nTime;
    QByteArray nBits;
    uint32_t nNonce;
    uint32_t nSize;

    Block(QByteArray& array, uint32_t size) : nSize(size)
    {
        uint32_t offset = 0;

        nVersion = ParseUint32R(array.mid(offset, VERSION_SIZE));
        offset += VERSION_SIZE;

        QByteArray previousHashArray = array.mid(offset, HASH_SIZE);
        hashPrevBlock = Reverse(previousHashArray);
        offset += HASH_SIZE;

        QByteArray merkleRootArray = array.mid(offset, MERKLE_ROOT_SIZE);
        hashMerkleRoot = Reverse(merkleRootArray);
        offset += MERKLE_ROOT_SIZE;

        nTime = ParseUint32R(array.mid(offset, TIME_SIZE));
        offset += TIME_SIZE;

        QByteArray bitsArray = array.mid(offset, BITS_SIZE);
        nBits = Reverse(bitsArray);
        offset += BITS_SIZE;

        nNonce = ParseUint32R(array.mid(offset, NONCE_SIZE));
        offset += NONCE_SIZE;
    }
};


std::ostream& operator<< (std::ostream& stream, const Block& block)
{
    stream << "Size: " << block.nSize << std::endl;
    stream << "Version: " << block.nVersion << std::endl;
    stream << "Hash of the previous block: " << block.hashPrevBlock.toHex().toStdString() << std::endl;
    stream << "Merkle root: " << block.hashMerkleRoot.toHex().toStdString() << std::endl;
    stream << "Time: " << block.nTime << std::endl;
    stream << "Bits: " << block.nBits.toHex().toStdString() << std::endl;
    stream << "Nonce: " << block.nNonce << std::endl;
    return stream;
}


#endif // BLOCK

