#include "validator.h"
#include "sha256.h"

#include <exception>
#include  <iomanip>

bool Validator::validateBlockChain(const Blockchain &chain){

    const std::vector<Block> &blocks = chain.getBlocks();

    //if(!validateBlock(*blocks.begin(),nullptr)) return false;
    for(auto it = ++blocks.begin(); it < blocks.end(); ++it) {
        if(!validateBlock(*it,*(it-1))) return false;
    }

    return true;
}

bool Validator::validateBlock(const Block &head, const Block &predecessor){

    //if (head == nullptr) throw new invalid_argument("block to be validated is null");

    //previous block header hash
    if(!verifyPreviousBlocHash(head,predecessor))
        return setIsValidBlockAttribute(head,false, "Invalid previous block hash");

    //block hash proof of work
    //if(!satisfyProofOfWork(head)) return setIsValidBlockAttribute(head,false, "Invalid proof of work");

    //time stamp not more than 2 hours in future
    uint32_t currentTime = static_cast<uint32_t>(time(NULL));
    if (!timestampNotTooNew(head,currentTime)) return setIsValidBlockAttribute(head,false, "Invalid timestamp");

    //Verify Merkle hash
    //if(!verifyMerkleHash(head)) return setIsValidBlockAttribute(head,false, "Invalid merkle root hash");

    return validateTransactions(head);
}

bool Validator::validateTransactions(const Block &block){

    const std::vector<Transaction> &transactions = block.tx;

    //transaction list nonempty
    if (!transactionListNonempty(transactions)) return setIsValidBlockAttribute(block,false, "Empty transaction list");

    //first transaction coinbase
    if(!isCoinbase(transactions.at(0))) return setIsValidBlockAttribute(block,false, "First transaction is not coinbase");

    //other transactions not coinbase
    for(auto it = (++transactions.begin()); it != transactions.end(); ++it){
        if(isCoinbase(*it)) return setIsValidBlockAttribute(block,false, "Transaction other then first is coinbase");
    }


    //For the coinbase (first) transaction, scriptSig length must be 2-100
    if(!isCoinbaseCorrectScriptSigLen(transactions.at(0))) return setIsValidBlockAttribute(block,false, "Coinbase script is wrong length");


    //validate all transactions
    for(auto it = transactions.begin(); it != transactions.end(); ++it){
        if(!validateTransaction(*it)) return setIsValidBlockAttribute(block,false, "Some of the transactions not valid");
    }
    return setIsValidBlockAttribute(block,true, "all good");
}

bool Validator::validateTransaction(const Transaction &transaction){
    //Make sure neither in or out lists are empty
    if(transaction.getInputs().size() == 0 || transaction.getOutputs().size() == 0) return false;

    //Size in bytes <= MAX_BLOCK_SIZE
    uint64_t size =  transaction.getOffsets().second - transaction.getOffsets().first;
    if(size > MAX_BLOCKFILE_SIZE) return false;

    //Each output value, as well as the total, must be in legal money range - TODO
    return true;
}

bool Validator::timestampNotTooNew(const Block &block,uint32_t timestamp){

    const uint32_t twoHoursInSeconds = 2*60*60;

    uint32_t blockTime = block.time;

    return (blockTime-twoHoursInSeconds)<timestamp;
}
bool Validator::verifyPreviousBlocHash(const Block &head, const Block &predecessor){

    //if(predecessor == nullptr) return true; //implicitly true if no predecessor provided

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
    const std::vector<TxIn>& inputs = transaction.getInputs();

    //coinbase has exactly one input
    if(inputs.size() != 1) return false;

    //hash of previous transaction of input is 0;
    uint256 hashPrev = inputs.begin()->getHashPrevTrans();
    unsigned char *hashDataBegin = hashPrev.begin();
    unsigned char* hashDataEnd = hashPrev.end();

    for(hashDataBegin; hashDataBegin < hashDataEnd; ++hashDataBegin) {
        if (*hashDataBegin != 0) return false;
    }

    //seq. num of coinbase == -1
    if(inputs.begin()->getSeqNumber() != 4294967295) return false; //this is in unsigned??
    return true;
}
bool Validator::isCoinbaseCorrectScriptSigLen(const Transaction &transaction){
    /*offsets offs = transaction.getOffsets();
    uint64_t size = offs.second - offs.first;
    if(size < 2 || size > 100) return false;*/
    return true;
}

uint256 Validator::hashBlock(const Block &block){

    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(block.binBuffer.get());
    ptr += block.headerOffsets.first;

    //correct hashing is strongly dependent on correct offsets - otherwise it all goes bye bye
    return HashX11<const unsigned char*>(ptr,block.headerOffsets.second-block.headerOffsets.first);
}

uint256 Validator::computeMerkleHash(const Block &block){
    std::cout << "Valid hash: " << block.hashMerkleRoot.ToString() << std::endl;
/*
    std::vector<uint256> leaves;
    const std::vector<Transaction> &transactions = block.tx;
    for(auto it = transactions.begin(); it < transactions.end(); it++){
        const unsigned char* ptr = reinterpret_cast<const unsigned char*>(block.binBuffer.get());
        ptr += it->getOffsets().first;
        uint64_t size = it->getOffsets().second - it->getOffsets().first;
        leaves.push_back(HashX11<const unsigned char*>(ptr,size));
    }

    return ComputeMerkleRoot(leaves);
    */




    /*
    std::cout << "Sha some fun" << std::endl;
    unsigned char tmpHashX[6];
    unsigned char tmpHashY[33];
    {
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,tmpHashX,5);
        sha256_final(&ctx,tmpHashY);
    }
    for(int j = 0; j <32; ++j){
        std::cout << std::hex << (int) tmpHashY[j] << std::dec;
    }
    std::cout << std::endl << "Context reset" << std::endl;

    //ctx = SHA256_CTX();
    unsigned char tmpHash1[6] = "hello";
    unsigned char tmpHash2[33];
    unsigned char tmpHash3[33];
    {
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,tmpHash1,5);
        sha256_final(&ctx,tmpHash2);
    }

    {
        SHA256_CTX ctx2;
        sha256_init(&ctx2);
        sha256_update(&ctx2,tmpHash2,32);
        sha256_final(&ctx2,tmpHash3);
    }


    std::cout << "sha 1: " << std::endl;
    for(int j = 0; j <32; ++j){
        std::cout << std::hex << (int) tmpHash2[j] << std::dec;
    }
    std::cout << std::endl << "sha 2: " << std::endl;
    for(int j = 0; j <32; ++j){
        std::cout << std::hex << (int) tmpHash3[j] << std::dec;
    }
    std::cout << std::endl;

    */

    const std::vector<Transaction> &transactions = block.tx;
    int baseNoPadding = transactions.size();
    int actualSize = baseNoPadding + baseNoPadding%2;
    unsigned char hashes[actualSize][32];

    //what should merkle tree do on single transaction?
    //use hash of that transaction as root

    //fill hashes for first round
    for(int i = 0; i < baseNoPadding; ++i){
        const unsigned char* ptr = reinterpret_cast<const unsigned char*>(block.binBuffer.get());
        uint64_t first = (transactions.at(i).getOffsets().first);
        ptr += first;
        //int posun = 5;
        //ptr += posun;
        uint64_t size = transactions.at(i).getOffsets().second - first;
        unsigned char tmpHash[32];
        {
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,ptr,size);
        sha256_final(&ctx,tmpHash);
        }
        {
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx,tmpHash,32);
        sha256_final(&ctx,hashes[i]);
        }
        //hashes[i] = HashX11<const unsigned char*>(ptr,size);
        std::cout << "Initial hash: ";
        for(int j = 31; j >=0; --j){
            std::cout << std::setfill('0') << std::setw(2) << std::hex << (int) hashes[i][j] << std::dec;
        }
        std::cout << std::endl;
    }

    if(baseNoPadding != actualSize){ // => one element more
        for(int j = 0; j <32; ++j){
            hashes[actualSize-1][j] = hashes[baseNoPadding-1][j];
        }
    }

    //actual computation
    while(actualSize != 1 && baseNoPadding != 1) {
        std::cout << "Next round" << std::endl;
        for(int i = 0, j=0; i < actualSize; i+=2,++j){
            unsigned char concat[64];
            int offset = 0;
            for(; offset < 32;++offset){
                concat[offset] = hashes[i][offset];
            }
            for(; offset < 64;++offset){
                concat[offset] = hashes[i+1][offset-32];
            }


            /*int offset = 0;
            for(offset = 31; offset >= 0;--offset){
                concat[offset] = hashes[i+1][offset];
            }
            for(offset = 63; offset >= 32;--offset){
                concat[offset] = hashes[i][offset]-32;
            }*/

            unsigned char tmpHash[32];
            {
            SHA256_CTX ctx;
            sha256_init(&ctx);
            sha256_update(&ctx,concat,64);
            sha256_final(&ctx,tmpHash);
            }
            {
            SHA256_CTX ctx;
            sha256_init(&ctx);
            sha256_update(&ctx,tmpHash,32);
            sha256_final(&ctx,hashes[j]);
            }

            //hashes[j] = HashX11<unsigned char*>(data,tmpSize);
            std::cout << "Generated hash: ";
            for(int q = 31; q >=0; --q){
                std::cout << std::setfill('0') << std::hex << (int) hashes[j][q] << std::dec;
            }
            std::cout << std::endl;
        }

        actualSize = actualSize/2;
        if(actualSize > 1 && actualSize%2 != 0){
            for(int j = 0; j <32; ++j){
                hashes[actualSize][j] = hashes[actualSize-1][j];
            }
            ++actualSize;
        }
    }

    std::vector<unsigned char> holder;
    for(int j = 0; j <32; ++j){
        holder.push_back(hashes[0][j]);
    }
    uint256 finalHash(holder);
    return finalHash;
}

bool Validator::setIsValidBlockAttribute(const Block& block, bool result, const char* message){
    validStat &stat = block.getValidStat();
    stat.first = result;
    stat.second = message;

    std::cout << block.getValidStat().second << std::endl;
    return result;
}


