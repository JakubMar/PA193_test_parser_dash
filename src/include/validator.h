#pragma once

#include <ctime>

#include "hash.h"
#include <block.h>
#include <blockchain.h>
#include <transaction.h>

class Validator
{
public:
    static bool validateBlockChain(const Blockchain &chain);
    static bool validateBlock(const Block &head, const Block &predecessor);

    friend class TestHelper;

private:

    static bool validateTransactions(const Block &block);
    static bool timestampNotTooNew(const Block &block, uint32_t timestamp);
    static bool verifyPreviousBlocHash(const Block &head, const Block &predecessor);
    static bool verifyMerkleHash(const Block &block);
    static bool satisfyProofOfWork(const Block &block); //TODO


    static bool validateTransaction(const Transaction &transaction); //TODO
    static bool transactionListNonempty(const std::vector<Transaction> &tx);

    static bool isCoinbase(const Transaction &transaction);
    static bool isCoinbaseCorrectScriptSigLen(const Transaction &transaction); //TODO

    static bool setIsValidBlockAttribute(const Block& block, bool result, const char* message);

    static uint256 hashBlock(const Block &block);
    static uint256 computeMerkleHash(const Block &block);
};


