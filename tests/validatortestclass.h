#pragma once

#include "validator.h"

class ValidatorTestClass
{
public:
    static bool validateBlockChain(const Blockchain &chain)
    {
        return Validator.validateBlockChain(chain);
    }


    static bool validateBlock(const Block &head, const Block &predecessor)
    {
        return Validator.validateBlock(head, predecessor);
    }


    static bool validateTransactions(const Block &block)
    {
        return Validator.validateTransactions(block);
    }


    static bool timestampNotTooNew(const Block &block)
    {
        return Validator.timestampNotTooNew(block);
    }


    static bool verifyPreviousBlocHash(const Block &head, const Block &predecessor)
    {
        return Validator.verifyPreviousBlocHash(head, predecessor);
    }


    static bool verifyMerkleHash(const Block &block)
    {
        return Validator.verifyMerkleHash(block);
    }


    static bool satisfyProofOfWork(const Block &block)
    {
        return Validator.satisfyProofOfWork(block);
    }


    static bool validateTransaction(const Transaction &transaction)
    {
        return Validator.validateTransaction(transaction);
    }


    static bool transactionListNonempty(const std::vector<Transaction> &tx)
    {
        return Validator.transactionListNonempty(tx);
    }


    static bool isCoinbase(const Transaction &transaction)
    {
        return Validator.isCoinbase(head, predecessor);
    }


    static bool isCoinbaseCorrectScriptSigLen(const Transaction &transaction)
    {
        return Validator.isCoinbaseCorrectScriptSigLen(transaction);
    }


    static uint256 hashBlock(const Block &block)
    {
        return Validator.hashBlock(block);
    }


    static uint256 computeMerkleHash(const Block &block)
    {
        return Validator.computeMerkleHash(block);
    }

};

