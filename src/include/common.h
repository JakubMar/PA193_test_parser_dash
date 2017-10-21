#ifndef COMMON
#define COMMON

#include <string.h>
#include <memory>


const char MAGIC_NUMBER[] = "\xbf\x0c\x6b\xbd";
const unsigned int MAX_BLOCKFILE_SIZE = 0x8000000; // 128 MiB
const unsigned int MAX_NUMBER_OF_BLOCKS = 10;

uint32_t ParseUint32(const char* array)
{
    uint32_t ret;
    memcpy(&ret, array, 4);
    return ret;
}

// Parse reverse array to unsigned int
uint32_t ParseUint32R(const char* array)
{
    return 0; //_0xFD_builtin_bswap32(ParseUint32(array)) - gcc function to change endian (if needed in future)
}


uint64_t ParseVarLength(const unsigned char* array)
{
    switch(array[0])
    {
        case 0xFD:
        {
            return *(reinterpret_cast<const uint16_t*>(&array[1]));
        }
        case 0xFE:
        {
            return *(reinterpret_cast<const uint32_t*>(&array[1]));
        }
        case 0xFF:
        {
            return *(reinterpret_cast<const uint64_t*>(&array[1]));
        }
    default:
        return reinterpret_cast<uint8_t>(array[0]);
    }


}

#endif // COMMON

