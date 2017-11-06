#pragma once

#include "validator.h"

class TestHelper
{
public:

    static Block CreateEmptyBlockObject()
    {
        return Block();
    }


    static Block CreateBlockObject(std::unique_ptr<char[]>& buffer, const uint256& merkle, const uint256& hashPrev,
                                        const offsets& BEOffsets, const uint32_t& bits, const uint32_t& nonce, const uint32_t& size,
                                        const uint32_t& time, const std::vector<Transaction>& trans, const uint32_t& version)
    {
        Block ret;
        ret.binBuffer = std::move(buffer);
        ret.hashMerkleRoot = merkle;
        ret.hashPrevBlock = hashPrev;
        ret.headerOffsets = BEOffsets;
        ret.bits = bits;
        ret.nonce = nonce;
        ret.size = size;
        ret.time = time;
        ret.tx = trans;
        ret.version = version;

        return ret;
    }


    static Transaction CreateEmptyTransactionObject()
    {
        return Transaction();
    }


    static Transaction CreateTransactionObject(const offsets& BEOffsets, const std::vector<TxIn>& inputs, const std::vector<TxOut>& outputs,
                                               const uint32_t& lockTime, const uint32_t& version)
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


    static TxIn CreateTxInObject(const uint256& hashPrev, const uint32_t& indexPrev, const uint32_t& seqNumber)
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


    static bool validateBlockChain(Blockchain &chain)
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
        uint32_t currentTime = static_cast<uint32_t>(time(NULL));
        return Validator::timestampNotTooNew(block,currentTime);
    }


    static bool verifyPreviousBlockHash(const Block &head, const Block &predecessor)
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


    static void setBlockTime(Block &block, const uint32_t &time)
    {
        block.time = time;
    }

    static void setBlockPrevhash(Block &block, const uint256 &hash)
    {
        block.hashPrevBlock = hash;
    }


    static void setBlockMerkelRoot(Block &block, const uint256 &root)
    {
        block.hashMerkleRoot = root;
    }


    static void setBlockOffsets(Block &block, const offsets &offset)
    {
        block.headerOffsets = offset;
    }


    static void setBlockBinBuffer(Block &block, std::unique_ptr<char[]> buffer)
    {
        block.binBuffer = std::move(buffer);
    }


    static void setBlockTx(Block &block, const std::vector<Transaction> &tx)
    {
        block.tx = tx;
    }


    static void setTransactionVersion(Transaction &trans, const uint32_t &value)
    {
        trans.version = value;
    }


    static void setTransactionInTrans(Transaction &trans, const std::vector<TxIn> &value)
    {
        trans.inTrans = value;
    }


    static void setTransactionOutTrans(Transaction &trans, const std::vector<TxOut> &value)
    {
        trans.outTrans = value;
    }


    static void setTransactionLockTime(Transaction &trans, const uint32_t &value)
    {
        trans.lockTime = value;
    }


    static void setTransactionBeginEndOffsets(Transaction &trans, const offsets &value)
    {
        trans.beginEndOffsets = value;
    }


























};

