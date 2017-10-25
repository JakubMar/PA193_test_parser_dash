#pragma once

#include <ctime>

#include <block.h>
#include <blockchain.h>
#include <transaction.h>

class Validator
{
public:
    static bool validateBlockChain(const Blockchain &chain); //TODO
    static bool validateBlock(const Block &head, const Block &predecessor);

private:

    static bool validateTransactions(const Block &block);
    static bool timestampNotTooOld(const Block &block); //TODO
    static bool verifyPreviousBlocHash(const Block &head, const Block &predecessor); //TODO
    static bool verifyMerkleHash(const Block &block); //TODO
    static bool satisfyProofOfWork(const Block &block); //TODO


    static bool validateTransaction(const Transaction &transaction); //TODO
    static bool transactionListNonempty(const std::vector<Transaction> &tx); //TODO

    static bool isCoinbase(const Transaction &transaction); //TODO
    static bool isCoinbaseCorrectScriptSigLen(const Transaction &transaction); //TODO

};
