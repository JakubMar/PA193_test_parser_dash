#pragma once

#include <string.h>
#include "uint256.h"
#include <memory>
#include <invalidblocksizeexcepion.h>
#include <invalidvarlengthexcepion.h>
#include <magicnumberexception.h>
#include <readfileexception.h>
#include <invalidtransactionsizeexcepion.h>

/**
 * Forward declaration
 */
class TestHelper;

const char MAGIC_NUMBER[] = "\xbf\x0c\x6b\xbd";
const unsigned int MAX_BLOCKFILE_SIZE = 0x8000000; // 128 MiB
const unsigned int MAX_NUMBER_OF_BLOCKS = 10;
const uint32_t MAGIC_NUMBER_SIZE = 4;
const uint32_t BLOCK_SIZE_SIZE = 4;
const uint32_t VERSION_SIZE = 4;
const uint32_t HASH_SIZE = 32;
const uint32_t MERKLE_ROOT_SIZE = 32;
const uint32_t TIME_SIZE = 4;
const uint32_t BITS_SIZE = 4;
const uint32_t NONCE_SIZE = 4;
const uint32_t BLOCK_HEADER_SIZE = VERSION_SIZE + HASH_SIZE + MERKLE_ROOT_SIZE + TIME_SIZE + BITS_SIZE + NONCE_SIZE;
const uint32_t VALUE_SIZE = 8;
const uint32_t INDEX_SIZE = 4;
const uint32_t SEQUENCE_NUM_SIZE = 4;


using varInt = std::pair<uint64_t,uint8_t>;
using offsets = std::pair<uint64_t,uint64_t>;
using validStat = std::pair<bool, std::string>;

/**
 * @brief ParseUint32 transforms raw buffer to uint32_t
 * @param array buffer with data
 * @return uint32_t number
 */
inline uint32_t ParseUint32(const char* array)
{
    uint32_t ret;
    memcpy(&ret, array, 4);
    return ret;
}

/**
 * @brief ParseUint64  transforms raw buffer to uint64_t
 * @param array buffer with data
 * @return uint64_t number
 */
inline uint64_t ParseUint64(const char* array)
{
    uint64_t ret;
    memcpy(&ret, array, 8);
    return ret;
}

/**
 * @brief ParseVarLength variable length integer value depends on the first byte
 * values can be uint8_t, uint16_t, uint32_t or uint64_t => 1 up to 8 bytes value
 * @param array buffer with data
 * @param size size of buffer
 * @return pair of value and number of read bytes
 */
inline varInt ParseVarLength(const unsigned char* array, size_t size)
{
    if (size == 0)
        throw InvalidVarLengthException();

    switch (array[0])
    {
    case 0xFD:
    {
        if (size < 3)
            throw InvalidVarLengthException();
        return varInt((*reinterpret_cast<const uint16_t*>(&array[1])), 3);
    }
    case 0xFE:
    {
        if (size < 5)
            throw InvalidVarLengthException();
        return varInt(*reinterpret_cast<const uint32_t*>(&array[1]),5);
    }
    case 0xFF:
    {
        if (size < 9)
            throw InvalidVarLengthException();
        return varInt(*reinterpret_cast<const uint64_t*>(&array[1]), 9);
    }
    default:
        return varInt(reinterpret_cast<uint8_t>(array[0]),1);
    }
}

/**
 * @brief ParseVarLength overloaded function for const char* array
 * @param array buffer with data
 * @param size size of buffer
 * @return pair of value and number of read bytes
 */
inline varInt ParseVarLength(const char* array, size_t size)
{
    return ParseVarLength(reinterpret_cast<const unsigned char*>(array), size);
}
