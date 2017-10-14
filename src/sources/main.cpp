#include <iostream>
#include <QFile>
#include "block.h"
#include "common.h"

using namespace std;

const QByteArray MAGIC_NUMBER = QByteArrayLiteral("\xbf\x0c\x6b\xbd");

int main()
{
    QFile file("./block.bin");

    if (!file.open(QIODevice::ReadOnly))
    {
        std::cout << "File cannot be open" << std::endl;
        return 0;
    }

    QByteArray fileContent = file.readAll();

    if(!fileContent.startsWith(MAGIC_NUMBER))
    {
        std::cout << "File does not start with magic number" << std::endl;
        return 0;
    }

    std::cout << "File starts with magic number" << std::endl;

    uint32_t size = ParseUint32R(fileContent.mid(4, 4));

    if(size > MAX_BLOCKFILE_SIZE)
    {
        std::cout << "Block size is invalid" << std::endl;
        return 0;
    }

    Block block(fileContent.remove(0, 8), size);

    std::cout << block << std::endl;

    return 0;
}

////block #1 header - taken binary represenation (no change in endianity)
//const unsigned char b1_header[] = {
// 0xbf, 0x0c, 0x6b, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xb6, 0x7a, 0x40, 0xf3, 0xcd, 0x58, 0x04, 0x43, 0x7a, 0x10,
// 0x8f, 0x10, 0x55, 0x33, 0x73, 0x9c, 0x37, 0xe6, 0x22, 0x9b, 0xc1, 0xad, 0xca, 0xb3, 0x85, 0x14, 0x0b, 0x59, 0xfd, 0x0f, 0x00, 0x00,
// 0xa7, 0x1c, 0x1a, 0xad, 0xe4, 0x4b, 0xf8, 0x42, 0x5b, 0xec, 0x0d, 0xeb, 0x61, 0x1c, 0x20, 0xb1, 0x6d, 0xa3, 0x44, 0x28, 0x18, 0xef,
// 0x20, 0x48, 0x9c, 0xa1, 0xe2, 0x51, 0x2b, 0xe4, 0x3e, 0xef, 0x81, 0x4c, 0xdb, 0x52, 0xf0, 0xff, 0x0f, 0x1e, 0xdb, 0xf7, 0x01, 0x00
// };

////result is                                               239a85fb2092e8b686d758918ab32c956029456c1d3e97a3f260913228773322
////expected result with proper endianity and formatting is 000007d91d1254d60e2dd1ae580383070a4ddffa4c64c2eeb4a2f9ecc0414343
//
//REQUIRE(HashX11<const unsigned char*>(b1_header, 88).ToString().compare("239a85fb2092e8b686d758918ab32c956029456c1d3e97a3f260913228773322") == 0);

/*
char buffer[] = {0x00,0x11};

buffer = read_resources();
block = parse(buffer);
if(block)
{
if(valid(block))
    {
     print(block);
    }
}
*/
