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
    /**
     * @brief validateTransactions validate all ransactions in the block
     * @param block block to check transactions
     * @return true if valid
     */
    static bool validateTransactions(const Block &block);
    /**
     * @brief timestampNotTooNew checks if timestamp is not more than 2 hours in the future
     * @param block block with timestamp
     * @param timestamp actual time
     * @return true if valid
     */
    static bool timestampNotTooNew(const Block &block, uint32_t timestamp);
    /**
     * @brief verifyPreviousBlocHash computes hash of previous block header and compares to hash saved in actual block
     * @param head actual block
     * @param predecessor block whose hash is computed
     * @return true if hashes are equal, false otherwise
     */
    static bool verifyPreviousBlocHash(const Block &head, const Block &predecessor);
    /**
     * @brief verifyMerkleHash compute merkle hash and compare with actual stored value
     * @param block block with transactions to compute merkle tree
     * @return true if valid
     */
    static bool verifyMerkleHash(const Block &block);
    /**
     * @brief validateTransaction check whether input and output transactions are not empty
     * @param transaction transaction to validate
     * @return true if valid
     */
    static bool validateTransaction(const Transaction &transaction);
    /**
     * @brief transactionListNonempty checks if there are some transactions
     * @param tx vector of transactions
     * @return true if vector is not empty
     */
    static bool transactionListNonempty(const std::vector<Transaction> &tx);
    /**
     * @brief isCoinbase checks whether and if only first transaction is coinbase
     * @param transaction transaction to check
     * @return true if valid
     */
    static bool isCoinbase(const Transaction &transaction);
    /**
     * @brief setIsValidBlockAttribute saves result of validation to block
     * @param block block to set result
     * @param result true if block is valid, false otherwise
     * @param message reason why block is invalid, "all good" if block is valid
     * @return result
     */
    static bool setIsValidBlockAttribute(const Block& block, bool result, const char* message);
    /**
     * @brief hashBlock uses X11 algorithm to hash block header
     * @param block block to compute hash of
     * @return hash of block header
     */
    static uint256 hashBlock(const Block &block);
    /**
     * @brief computeMerkleHash computes merkle hash (tree of hashes with padding) of all transactions,
     * @param block block to compute merkle hash of
     * @return merkle hash
     */
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


