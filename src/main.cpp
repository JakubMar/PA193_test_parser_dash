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
