#ifndef COMMON
#define COMMON

#include <QString>

const unsigned int MAX_BLOCKFILE_SIZE = 0x8000000; // 128 MiB

QByteArray Reverse(const QByteArray& other)
{
    QByteArray reverse;
    for( QByteArray::const_iterator i = other.constEnd(); i !=other.constBegin(); )
    {
        --i;
        reverse += *i;
    }
    return reverse;
}

uint32_t ParseUint32(const QByteArray& array)
{
    return array.toHex().toUInt(0, 16);
}

// Parse reverse array to unsigned int
uint32_t ParseUint32R(const QByteArray& array)
{
    return ParseUint32(Reverse(array));
}

#endif // COMMON

