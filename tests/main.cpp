#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <string>
#include "hash.h"
#include "blockchain.h"


TEST_CASE("Hash tests")
{
    SECTION("Hash X11")
    {
    //block #1 header - taken binary represenation (no change in endianity)
    const unsigned char b1_header[] = {
     0xbf, 0x0c, 0x6b, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xb6, 0x7a, 0x40, 0xf3, 0xcd, 0x58, 0x04, 0x43, 0x7a, 0x10,
     0x8f, 0x10, 0x55, 0x33, 0x73, 0x9c, 0x37, 0xe6, 0x22, 0x9b, 0xc1, 0xad, 0xca, 0xb3, 0x85, 0x14, 0x0b, 0x59, 0xfd, 0x0f, 0x00, 0x00,
     0xa7, 0x1c, 0x1a, 0xad, 0xe4, 0x4b, 0xf8, 0x42, 0x5b, 0xec, 0x0d, 0xeb, 0x61, 0x1c, 0x20, 0xb1, 0x6d, 0xa3, 0x44, 0x28, 0x18, 0xef,
     0x20, 0x48, 0x9c, 0xa1, 0xe2, 0x51, 0x2b, 0xe4, 0x3e, 0xef, 0x81, 0x4c, 0xdb, 0x52, 0xf0, 0xff, 0x0f, 0x1e, 0xdb, 0xf7, 0x01, 0x00
     };

    //result is                                               239a85fb2092e8b686d758918ab32c956029456c1d3e97a3f260913228773322
    //expected result with proper endianity and formatting is 000007d91d1254d60e2dd1ae580383070a4ddffa4c64c2eeb4a2f9ecc0414343

    REQUIRE(HashX11<const unsigned char*>(b1_header, 88).ToString().compare("239a85fb2092e8b686d758918ab32c956029456c1d3e97a3f260913228773322") == 0);
    }
}


TEST_CASE("Block tests")
{
    SECTION("Valid block") {

        //block #1 without magic number and size
        const unsigned char test_block[] = {
            0x02, 0x00, 0x00, 0x00, 0xB6, 0x7A, 0x40, 0xF3, 0xCD, 0x58, 0x04, 0x43, 0x7A, 0x10, 0x8F, 0x10,
            0x55, 0x33, 0x73, 0x9C, 0x37, 0xE6, 0x22, 0x9B, 0xC1, 0xAD, 0xCA, 0xB3, 0x85, 0x14, 0x0B, 0x59,
            0xFD, 0x0F, 0x00, 0x00, 0xA7, 0x1C, 0x1A, 0xAD, 0xE4, 0x4B, 0xF8, 0x42, 0x5B, 0xEC, 0x0D, 0xEB,
            0x61, 0x1C, 0x20, 0xB1, 0x6D, 0xA3, 0x44, 0x28, 0x18, 0xEF, 0x20, 0x48, 0x9C, 0xA1, 0xE2, 0x51,
            0x2B, 0xE4, 0x3E, 0xEF, 0x81, 0x4C, 0xDB, 0x52, 0xF0, 0xFF, 0x0F, 0x1E, 0xDB, 0xF7, 0x01, 0x00,
            0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x51, 0x01, 0x01, 0x06, 0x2F,
            0x50, 0x32, 0x53, 0x48, 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x74, 0x3B, 0xA4, 0x0B, 0x00,
            0x00, 0x00, 0x23, 0x21, 0x03, 0xA6, 0x98, 0x50, 0x24, 0x3C, 0x99, 0x3C, 0x06, 0x45, 0xA6, 0xE8,
            0xB3, 0x8C, 0x77, 0x41, 0x74, 0x17, 0x4C, 0xC7, 0x66, 0xCD, 0x3E, 0xC2, 0x14, 0x0A, 0xFD, 0x24,
            0xD8, 0x31, 0xB8, 0x4C, 0x41, 0xAC, 0x00, 0x00, 0x00, 0x00
         };

        uint32_t expectedVersion = 2;
        std::string expectedHashPrevBlock = "00000ffd590b1485b3caadc19b22e6379c733355108f107a430458cdf3407ab6";
        std::string expectedHashMerkleRoot = "ef3ee42b51e2a19c4820ef182844a36db1201c61eb0dec5b42f84be4ad1a1ca7";
        uint32_t expectedTime = 1390103681;
        uint32_t expectedBits = 504365040;
        uint32_t expectedNonce = 128987;
        uint32_t expectedSize = 186;

        Block block(reinterpret_cast<const char*>(test_block), 186);

        REQUIRE(block.nVersion == expectedVersion);
        REQUIRE(block.hashPrevBlock.ToString() == expectedHashPrevBlock);
        REQUIRE(block.hashMerkleRoot.ToString() == expectedHashMerkleRoot);
        REQUIRE(block.nTime == expectedTime);
        REQUIRE(block.nBits == expectedBits);
        REQUIRE(block.nNonce == expectedNonce);
        REQUIRE(block.nSize == expectedSize);
    }
}


TEST_CASE("Blockchain tests")
{
    SECTION("One valid block") {

        //block #1 with everything
        const unsigned char test_block[] = {
            0xbf, 0x0c, 0x6b, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xB6, 0x7A, 0x40, 0xF3,
            0xCD, 0x58, 0x04, 0x43, 0x7A, 0x10, 0x8F, 0x10, 0x55, 0x33, 0x73, 0x9C, 0x37, 0xE6, 0x22, 0x9B,
            0xC1, 0xAD, 0xCA, 0xB3, 0x85, 0x14, 0x0B, 0x59, 0xFD, 0x0F, 0x00, 0x00, 0xA7, 0x1C, 0x1A, 0xAD,
            0xE4, 0x4B, 0xF8, 0x42, 0x5B, 0xEC, 0x0D, 0xEB, 0x61, 0x1C, 0x20, 0xB1, 0x6D, 0xA3, 0x44, 0x28,
            0x18, 0xEF, 0x20, 0x48, 0x9C, 0xA1, 0xE2, 0x51, 0x2B, 0xE4, 0x3E, 0xEF, 0x81, 0x4C, 0xDB, 0x52,
            0xF0, 0xFF, 0x0F, 0x1E, 0xDB, 0xF7, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
            0xFF, 0xFF, 0x0A, 0x51, 0x01, 0x01, 0x06, 0x2F, 0x50, 0x32, 0x53, 0x48, 0x2F, 0xFF, 0xFF, 0xFF,
            0xFF, 0x01, 0x00, 0x74, 0x3B, 0xA4, 0x0B, 0x00, 0x00, 0x00, 0x23, 0x21, 0x03, 0xA6, 0x98, 0x50,
            0x24, 0x3C, 0x99, 0x3C, 0x06, 0x45, 0xA6, 0xE8, 0xB3, 0x8C, 0x77, 0x41, 0x74, 0x17, 0x4C, 0xC7,
            0x66, 0xCD, 0x3E, 0xC2, 0x14, 0x0A, 0xFD, 0x24, 0xD8, 0x31, 0xB8, 0x4C, 0x41, 0xAC, 0x00, 0x00,
            0x00, 0x00
         };

        const std::string FILE_NAME =  "./blockchainTest1.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_block), 194);
        file.close();

        Blockchain chain(FILE_NAME);
        chain.parseFile();

        Block block = chain.getBlocks()[0];

        uint32_t expectedVersion = 2;
        std::string expectedHashPrevBlock = "00000ffd590b1485b3caadc19b22e6379c733355108f107a430458cdf3407ab6";
        std::string expectedHashMerkleRoot = "ef3ee42b51e2a19c4820ef182844a36db1201c61eb0dec5b42f84be4ad1a1ca7";
        uint32_t expectedTime = 1390103681;
        uint32_t expectedBits = 504365040;
        uint32_t expectedNonce = 128987;
        uint32_t expectedSize = 186;

        REQUIRE(block.nVersion == expectedVersion);
        REQUIRE(block.hashPrevBlock.ToString() == expectedHashPrevBlock);
        REQUIRE(block.hashMerkleRoot.ToString() == expectedHashMerkleRoot);
        REQUIRE(block.nTime == expectedTime);
        REQUIRE(block.nBits == expectedBits);
        REQUIRE(block.nNonce == expectedNonce);
        REQUIRE(block.nSize == expectedSize);
    }


    SECTION("Two valid blocks") {

        //2 * block #1 with everything
        const unsigned char test_blocks[] = {
            0xbf, 0x0c, 0x6b, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xB6, 0x7A, 0x40, 0xF3,
            0xCD, 0x58, 0x04, 0x43, 0x7A, 0x10, 0x8F, 0x10, 0x55, 0x33, 0x73, 0x9C, 0x37, 0xE6, 0x22, 0x9B,
            0xC1, 0xAD, 0xCA, 0xB3, 0x85, 0x14, 0x0B, 0x59, 0xFD, 0x0F, 0x00, 0x00, 0xA7, 0x1C, 0x1A, 0xAD,
            0xE4, 0x4B, 0xF8, 0x42, 0x5B, 0xEC, 0x0D, 0xEB, 0x61, 0x1C, 0x20, 0xB1, 0x6D, 0xA3, 0x44, 0x28,
            0x18, 0xEF, 0x20, 0x48, 0x9C, 0xA1, 0xE2, 0x51, 0x2B, 0xE4, 0x3E, 0xEF, 0x81, 0x4C, 0xDB, 0x52,
            0xF0, 0xFF, 0x0F, 0x1E, 0xDB, 0xF7, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
            0xFF, 0xFF, 0x0A, 0x51, 0x01, 0x01, 0x06, 0x2F, 0x50, 0x32, 0x53, 0x48, 0x2F, 0xFF, 0xFF, 0xFF,
            0xFF, 0x01, 0x00, 0x74, 0x3B, 0xA4, 0x0B, 0x00, 0x00, 0x00, 0x23, 0x21, 0x03, 0xA6, 0x98, 0x50,
            0x24, 0x3C, 0x99, 0x3C, 0x06, 0x45, 0xA6, 0xE8, 0xB3, 0x8C, 0x77, 0x41, 0x74, 0x17, 0x4C, 0xC7,
            0x66, 0xCD, 0x3E, 0xC2, 0x14, 0x0A, 0xFD, 0x24, 0xD8, 0x31, 0xB8, 0x4C, 0x41, 0xAC, 0x00, 0x00,
            0x00, 0x00,
            0xbf, 0x0c, 0x6b, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xB6, 0x7A, 0x40, 0xF3,
            0xCD, 0x58, 0x04, 0x43, 0x7A, 0x10, 0x8F, 0x10, 0x55, 0x33, 0x73, 0x9C, 0x37, 0xE6, 0x22, 0x9B,
            0xC1, 0xAD, 0xCA, 0xB3, 0x85, 0x14, 0x0B, 0x59, 0xFD, 0x0F, 0x00, 0x00, 0xA7, 0x1C, 0x1A, 0xAD,
            0xE4, 0x4B, 0xF8, 0x42, 0x5B, 0xEC, 0x0D, 0xEB, 0x61, 0x1C, 0x20, 0xB1, 0x6D, 0xA3, 0x44, 0x28,
            0x18, 0xEF, 0x20, 0x48, 0x9C, 0xA1, 0xE2, 0x51, 0x2B, 0xE4, 0x3E, 0xEF, 0x81, 0x4C, 0xDB, 0x52,
            0xF0, 0xFF, 0x0F, 0x1E, 0xDB, 0xF7, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
            0xFF, 0xFF, 0x0A, 0x51, 0x01, 0x01, 0x06, 0x2F, 0x50, 0x32, 0x53, 0x48, 0x2F, 0xFF, 0xFF, 0xFF,
            0xFF, 0x01, 0x00, 0x74, 0x3B, 0xA4, 0x0B, 0x00, 0x00, 0x00, 0x23, 0x21, 0x03, 0xA6, 0x98, 0x50,
            0x24, 0x3C, 0x99, 0x3C, 0x06, 0x45, 0xA6, 0xE8, 0xB3, 0x8C, 0x77, 0x41, 0x74, 0x17, 0x4C, 0xC7,
            0x66, 0xCD, 0x3E, 0xC2, 0x14, 0x0A, 0xFD, 0x24, 0xD8, 0x31, 0xB8, 0x4C, 0x41, 0xAC, 0x00, 0x00,
            0x00, 0x00
         };

        const std::string FILE_NAME =  "./blockchainTest1.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_blocks), 2 * 194);
        file.close();

        Blockchain chain(FILE_NAME);
        chain.parseFile();

        Block block1 = chain.getBlocks()[0];
        Block block2 = chain.getBlocks()[1];

        uint32_t expectedVersion = 2;
        std::string expectedHashPrevBlock = "00000ffd590b1485b3caadc19b22e6379c733355108f107a430458cdf3407ab6";
        std::string expectedHashMerkleRoot = "ef3ee42b51e2a19c4820ef182844a36db1201c61eb0dec5b42f84be4ad1a1ca7";
        uint32_t expectedTime = 1390103681;
        uint32_t expectedBits = 504365040;
        uint32_t expectedNonce = 128987;
        uint32_t expectedSize = 186;

        REQUIRE(block1.nVersion == expectedVersion);
        REQUIRE(block1.hashPrevBlock.ToString() == expectedHashPrevBlock);
        REQUIRE(block1.hashMerkleRoot.ToString() == expectedHashMerkleRoot);
        REQUIRE(block1.nTime == expectedTime);
        REQUIRE(block1.nBits == expectedBits);
        REQUIRE(block1.nNonce == expectedNonce);
        REQUIRE(block1.nSize == expectedSize);

        REQUIRE(block2.nVersion == expectedVersion);
        REQUIRE(block2.hashPrevBlock.ToString() == expectedHashPrevBlock);
        REQUIRE(block2.hashMerkleRoot.ToString() == expectedHashMerkleRoot);
        REQUIRE(block2.nTime == expectedTime);
        REQUIRE(block2.nBits == expectedBits);
        REQUIRE(block2.nNonce == expectedNonce);
        REQUIRE(block2.nSize == expectedSize);
    }


    SECTION("Magic number cannot be read") {

        const unsigned char test_blocks[] = {
            0xbf, 0x0c, 0x6b
         };

        const std::string FILE_NAME =  "./blockchainTest2.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_blocks), 3);
        file.close();

        Blockchain chain(FILE_NAME);
        REQUIRE_THROWS_WITH(chain.parseFile(), "Reading magic number from the file was not succesfull");
    }


    SECTION("File does not begin with magic number") {

        const unsigned char test_blocks[] = {
            0xbf, 0x0c, 0x6b, 0x00
         };

        const std::string FILE_NAME =  "./blockchainTest2.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_blocks), 4);
        file.close();

        Blockchain chain(FILE_NAME);
        REQUIRE_THROWS_AS(chain.parseFile(), MagicNumberException);
    }


    SECTION("Size cannot be read") {

        const unsigned char test_blocks[] = {
            0xbf, 0x0c, 0x6b, 0xbd, 0x00
         };

        const std::string FILE_NAME =  "./blockchainTest2.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_blocks), 5);
        file.close();

        Blockchain chain(FILE_NAME);
        REQUIRE_THROWS_WITH(chain.parseFile(), "Reading size of the block from the file was not succesfull");
    }


    SECTION("Invalid size") {

        const unsigned char test_blocks[] = {
            0xbf, 0x0c, 0x6b, 0xbd, 0xff, 0xff, 0xff, 0xff
         };

        const std::string FILE_NAME =  "./blockchainTest2.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_blocks), 8);
        file.close();

        Blockchain chain(FILE_NAME);
        REQUIRE_THROWS_AS(chain.parseFile(), InvalidBlockSizeException);
    }


    SECTION("Invalid size of content") {

        const unsigned char test_blocks[] = {
            0xbf, 0x0c, 0x6b, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x02
         };

        const std::string FILE_NAME =  "./blockchainTest2.bin";

        std::ofstream file(FILE_NAME);
        file.write(reinterpret_cast<const char*>(test_blocks), 9);
        file.close();

        Blockchain chain(FILE_NAME);
        REQUIRE_THROWS_WITH(chain.parseFile(), "Reading content of block from file was not succesfull");
    }
}


TEST_CASE("ParseVarLength tests")
{
    SECTION("Valid uint8_t length")
    {
    const unsigned char len_buffer[] = { 0x57 };

    uint8_t expectedValue = 0x57;
    uint8_t actualValue = ParseVarLength(len_buffer);

    REQUIRE(expectedValue == actualValue);
    }


    SECTION("Valid uint16_t length")
    {
    const unsigned char len_buffer[] = { 0xFD, 0xFC, 0x8A };

    uint16_t expectedValue = 0x8AFC;
    uint16_t actualValue = ParseVarLength(len_buffer);

    REQUIRE(expectedValue == actualValue);
    }


    SECTION("Valid uint32_t length")
    {
    const unsigned char len_buffer[] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF };

    uint32_t expectedValue = 0xFFFFFFFF;
    uint32_t actualValue = ParseVarLength(len_buffer);

    REQUIRE(expectedValue == actualValue);
    }


    SECTION("Valid uint64_t length")
    {
    const unsigned char len_buffer[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};

    uint64_t expectedValue = 0x100000000;
    uint64_t actualValue = ParseVarLength(len_buffer);

    REQUIRE(expectedValue == actualValue);
    }
}

#endif // CATCH_CONFIG_MAIN
