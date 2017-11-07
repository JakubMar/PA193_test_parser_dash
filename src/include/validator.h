#pragma once

#include <ctime>

#include "hash.h"
#include <block.h>
#include <blockchain.h>
#include <transaction.h>

/**
 * @brief The Validator class provides methods for semantic validation of blockchain
 */
class Validator
{
private:
    static bool validateTransactions(const Block &block);
    static bool timestampNotTooNew(const Block &block, uint32_t timestamp);
    static bool verifyPreviousBlocHash(const Block &head, const Block &predecessor);
    static bool verifyMerkleHash(const Block &block);
    static bool validateTransaction(const Transaction &transaction);
    static bool transactionListNonempty(const std::vector<Transaction> &tx);
    static bool isCoinbase(const Transaction &transaction);
    static bool setIsValidBlockAttribute(const Block& block, bool result, const char* message);
    static uint256 hashBlock(const Block &block);
    static uint256 computeMerkleHash(const Block &block);

public:
    /**
     * @brief validateBlockChain validates whole blockchain, iteratively validates all blocks
     * @param chain blockchain to validate
     * @return true if whole blockchain is valid
     */
    static bool validateBlockChain(const Blockchain &chain);

    /**
     * @brief validateBlock validate one block
     * @param head block to validate
     * @param predecessor previous block from blockchain
     * @return true if block is valid
     */
    static bool validateBlock(const Block &head, const Block &predecessor);

    /**
     * @brief friend class for testing
     */
    friend class TestHelper;
};


