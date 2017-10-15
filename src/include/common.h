#ifndef COMMON
#define COMMON

#include <string.h>

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
    return 0; //__builtin_bswap32(ParseUint32(array)) - gcc function to change endian (if needed in future)
}

#endif // COMMON

