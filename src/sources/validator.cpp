#include "validator.h"

bool Validator::validateBlockChain(const Blockchain &chain){

    const std::vector<Block> &blocks = chain.getBlocks();

    for(auto it = ++blocks.begin(); it < blocks.end(); ++it) {
        //first block is not validated at all in this construction
        if(!validateBlock(*it,*(it-1))) return false;
    }

    return true;
}

bool Validator::validateBlock(const Block &head, const Block &predecessor){

    //previous block header hash
    if(!verifyPreviousBlocHash(head,predecessor)) return false;

    //block hash proof of work
    if(!satisfyProofOfWork(head)) return false;

    //time stamp not more than 2 hours in future
    if (!timestampNotTooNew(head)) return false;

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
    for(auto it = (++transactions.begin()); it != transactions.end(); ++it){
        if(isCoinbase(*it)) return false;
    }


    //For the coinbase (first) transaction, scriptSig length must be 2-100
    if(!isCoinbaseCorrectScriptSigLen(transactions.at(0))) return false;


    //validate all transactions
    for(auto it = transactions.begin(); it != transactions.end(); ++it){
        if(!validateTransaction(*it)) return false;
    }
    return true;
}

bool Validator::validateTransaction(const Transaction &transaction){
    //apply "tx" checks 2-4
    return false;
}

bool Validator::timestampNotTooNew(const Block &block){

    const uint32_t twoHoursInSeconds = 2*60*60;

    uint32_t currentTime = static_cast<uint32_t>(time(NULL));

    uint32_t blockTime = block.nTime;

    return (blockTime-twoHoursInSeconds)<currentTime;
}
bool Validator::verifyPreviousBlocHash(const Block &head, const Block &predecessor){

    uint256 predecessorHash = hashBlock(predecessor);

    return predecessorHash == head.hashPrevBlock;
}
bool Validator::verifyMerkleHash(const Block &block){
    return  computeMerkleHash(block) == block.hashMerkleRoot;
}
bool Validator::satisfyProofOfWork(const Block &block){

    //this might not be implementable without further info - proof of work dynamically changes
    return false;
}

bool Validator::transactionListNonempty(const std::vector<Transaction> &tx){
    return tx.size() == 0 ? false : true;
}

bool Validator::isCoinbase(const Transaction &transaction){
    return false;
}
bool Validator::isCoinbaseCorrectScriptSigLen(const Transaction &transaction){
    return false;
}

uint256 Validator::hashBlock(const Block &block){

    //this is a bit dirty trick
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(block.binBuffer.get());
    ptr += block.headerOffsets.first;

    //correct hashing is strongly dependent on correct offsets - otherwise it all goes bye bye
    return HashX11<const unsigned char*>(ptr,block.headerOffsets.second-block.headerOffsets.first);
}

uint256 Validator::computeMerkleHash(const Block &block){
    const std::vector<Transaction> &transactions = block.nTx;
    int baseNoPadding = transactions.size();
    int actualSize = baseNoPadding + baseNoPadding%2;
    uint256 hashes[actualSize];

    //what should merkle tree do on single transaction?
    //I suppose hash itself twice and than hash sum as normaly

    //fill hashes for first round
    for(int i = 0; i < baseNoPadding; ++i){
        const unsigned char* ptr = reinterpret_cast<const unsigned char*>(block.binBuffer.get());
        ptr += transactions.at(i).GetOffsets().first;
        uint64_t size = transactions.at(i).GetOffsets().second - transactions.at(i).GetOffsets().first;
        hashes[i] = HashX11<const unsigned char*>(ptr,size);
    }

    if(baseNoPadding != actualSize){ // => one element more
        hashes[actualSize-1] = hashes[baseNoPadding-1];
    }

    //actual computation
    while(actualSize != 1) {
        for(int i = 0, j=0; i < actualSize; i+=2,++j){
            const uint256 sum; //hashes[i] + hashes[i+1];
          //  hashes[j] = HashX11<const uint256>(sum,sizeof(uint256));
        }

        actualSize = actualSize/2;
        if(actualSize%2 != 0){
            hashes[actualSize] = hashes[actualSize-1];
            ++actualSize;
        }
    }

    return hashes[0];
}


