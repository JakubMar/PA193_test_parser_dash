#pragma once

#include "validator.h"

class TestHelper
{
public:
    static Block CreateEmptyBlockObject()
    {
        return Block();
    }


    static Block CreateEmptyBlockObject(std::unique_ptr<char[]>& buffer, const uint256& merkle, const uint256& hashPrev,
                                        offsets& BEOffsets, uint32_t& bits, uint32_t& nonce, uint32_t& size, uint32_t& time,
                                        std::vector<Transaction>& trans, uint32_t& version)
    {
        Block ret;
        ret.binBuffer = std::move(buffer);
        ret.hashMerkleRoot = merkle;
        ret.hashPrevBlock = hashPrev;
        ret.headerOffsets = BEOffsets;
        ret.nBits = bits;
        ret.nNonce = nonce;
        ret.nSize = size;
        ret.nTime = time;
        ret.nTx = trans;
        ret.nVersion = version;

        return ret;
    }


    static Transaction CreateEmptyTransactionObject()
    {
        return Transaction();
    }


    static Transaction CreateTransactionObject(offsets& BEOffsets, std::vector<TxIn>& inputs, std::vector<TxOut>& outputs,
                                                    uint32_t& lockTime, uint32_t& version)
    {
        Transaction ret;
        ret.beginEndOffsets = BEOffsets;
        ret.inTrans = inputs;
        ret.lockTime = lockTime;
        ret.outTrans = outputs;
        ret.version = version;

        return ret;
    }


    static TxIn CreateEmptyTxInObject()
    {
        return TxIn();
    }


    static TxIn CreateTxInObject(const uint256& hashPrev, const uint32_t& indexPrev, uint32_t& seqNumber)
    {
        TxIn ret;
        ret.hashPrevTrans = hashPrev;
        ret.indexPrevTrans = indexPrev;
        ret.seqNumber = seqNumber;

        return ret;
    }


    static TxOut CreateEmptyTxOutObject()
    {
        return TxOut();
    }


    static TxOut CreateTxOutObject(const uint64_t& value)
    {
        TxOut ret;
        ret.value = value;

        return ret;
    }


    static bool validateBlockChain(const Blockchain &chain)
    {
        return Validator::validateBlockChain(chain);
    }


    static bool validateBlock(const Block &head, const Block &predecessor)
    {
        return Validator::validateBlock(head, predecessor);
    }


    static bool validateTransactions(const Block &block)
    {
        return Validator::validateTransactions(block);
    }


    static bool timestampNotTooNew(const Block &block)
    {
        return Validator::timestampNotTooNew(block);
    }


    static bool verifyPreviousBlocHash(const Block &head, const Block &predecessor)
    {
        return Validator::verifyPreviousBlocHash(head, predecessor);
    }


    static bool verifyMerkleHash(const Block &block)
    {
        return Validator::verifyMerkleHash(block);
    }


    static bool satisfyProofOfWork(const Block &block)
    {
        return Validator::satisfyProofOfWork(block);
    }


    static bool validateTransaction(const Transaction &transaction)
    {
        return Validator::validateTransaction(transaction);
    }


    static bool transactionListNonempty(const std::vector<Transaction> &tx)
    {
        return Validator::transactionListNonempty(tx);
    }


    static bool isCoinbase(const Transaction &transaction)
    {
        return Validator::isCoinbase(transaction);
    }


    static bool isCoinbaseCorrectScriptSigLen(const Transaction &transaction)
    {
        return Validator::isCoinbaseCorrectScriptSigLen(transaction);
    }


    static uint256 hashBlock(const Block &block)
    {
        return Validator::hashBlock(block);
    }


    static uint256 computeMerkleHash(const Block &block)
    {
        return Validator::computeMerkleHash(block);
    }
};

