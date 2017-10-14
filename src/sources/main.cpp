#include <iostream>
#include "block.h"
#include "common.h"
#include <fstream>

using namespace std;

const char MAGIC_NUMBER[] = "\xbf\x0c\x6b\xbd";

int main()
{
    ifstream file;
    file.open("./block.bin");

    if (!file.is_open())
    {
        std::cout << "File cannot be open" << std::endl;
        return 0;
    }

    const unsigned int SIZE = 4;

    char buffer[SIZE];
    file.read(buffer, SIZE);

    if(strncmp(buffer, MAGIC_NUMBER, SIZE) != 0)
    {
        std::cout << "File does not start with magic number" << std::endl;
        return 0;
    }

    std::cout << "File starts with magic number" << std::endl;

    uint32_t block_size;
    file.read(reinterpret_cast<char*>(&block_size), 4);

    if(block_size > MAX_BLOCKFILE_SIZE)
    {
        std::cout << "Block size: " << block_size << " is invalid" << std::endl;
        return 0;
    }

    char* block_buffer = new char[block_size];
    file.read(block_buffer, block_size);

    std::cout << "Block size: " << block_size  << std::endl;

    Block block(block_buffer, block_size);

    std::cout << block << std::endl;

    delete[] block_buffer;
    file.close();
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
