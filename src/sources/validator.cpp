#include "validator.h"

bool Validator::validateBlockChain(const Blockchain &chain){

    return false;
}

bool Validator::validateBlock(const Block &head, const Block &predecessor){

    //previous block header hash
    if(!verifyPreviousBlocHash(head,predecessor)) return false;

    //block hash proof of work
    if(!satisfyProofOfWork(head)) return false;

    //time stamp not more than 2 hours in future
    if (!timestampNotTooOld(head)) return false;

    //Verify Merkle hash
    if(!verifyMerkleHash(head)) return false;

    return true;
}

bool Validator::validateTransactions(const Block &block){

    const std::vector<Transaction> &transactions = block.nTx;

    //transaction list nonempty
    if (!transactionListNonempty(transactions)) return false;

    //first transaction coinbase
    if(!isCoinbase(transactions.at(0))) return false;

    //other transactions not coinbase
    for(std::vector<Transaction>::iterator it = (++transactions.begin()); it != transactions.end(); ++it){
        if(isCoinbase(*it)) return false;
    }


    //For the coinbase (first) transaction, scriptSig length must be 2-100
    if(!isCoinbaseCorrectScriptSigLen(transactions.at(0))) return false;


    //validate all transactions
    for(std::vector<Transaction>::iterator it = transactions.begin(); it != transactions.end(); ++it){
        if(!validateTransaction(*it)) return false;
    }
}

bool Validator::validateTransaction(const Transaction &transaction){
    //apply "tx" checks 2-4
}

bool Validator::timestampNotTooOld(const Block &block){
    return false;
}
bool Validator::verifyPreviousBlocHash(const Block &head, const Block &predecessor){
    return false;
}
bool Validator::verifyMerkleHash(const Block &block){
    return false;
}
bool Validator::satisfyProofOfWork(const Block &block){
    return false;
}

bool Validator::transactionListNonempty(const std::vector<Transaction> &tx){
    return false;
}

bool Validator::isCoinbase(const Transaction &transaction){
    return false;
}
bool Validator::isCoinbaseCorrectScriptSigLen(const Transaction &transaction){
    return false;
}
