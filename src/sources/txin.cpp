#include "txin.h"
#include "invalidtransactionsizeexcepion.h"

TxIn::TxIn(const char *buffer, uint32_t &globalOffset, size_t &unread_size)
{
    uint32_t localOff = 0;

    //HASH_PREV_TRANS
    if(unread_size < HASH_SIZE)
        throw InvalidTransactionSizeException("TxIn Hash");
    memcpy(&hashPrevTrans, buffer, HASH_SIZE);
    localOff += HASH_SIZE;
    unread_size -= HASH_SIZE;

    //INDEX_PREV_TRANS
    if(unread_size < INDEX_SIZE)
        throw InvalidTransactionSizeException("TxIn Index");
    indexPrevTrans = ParseUint32(buffer);
    localOff += INDEX_SIZE;
    unread_size -= INDEX_SIZE;

    //SCRIPT
    varInt scriptLen = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer), unread_size);
    localOff += scriptLen.second;
    unread_size -= scriptLen.second;

    if(unread_size < scriptLen.first)
        throw InvalidTransactionSizeException("TxIn Script");

//    std::unique_ptr<char[]> tmpScript(new char[scriptLen.first]);
//    memcpy(tmpScript.get(), buffer + localOff, scriptLen.first);
//    script = std::move(tmpScript);

    localOff += scriptLen.first;
    unread_size -= scriptLen.first;

    //SEQUENCE NUMBER
    if(unread_size < SEQUENCE_NUM_SIZE)
        throw InvalidTransactionSizeException("TxIn Sequence");
    seqNumber = ParseUint32(buffer);
    localOff += SEQUENCE_NUM_SIZE;
    unread_size -= SEQUENCE_NUM_SIZE;

    globalOffset += localOff;
}


uint32_t TxIn::GetSeqNumber() const
{
    return seqNumber;
}


std::ostream& operator<< (std::ostream& stream, const TxIn& tin)
{
    stream << "----------TxIn----------: " << std::endl;
    stream << "\tHash of the previous out transaction: " << tin.hashPrevTrans.GetHex() << std::endl;
    stream << "\tIndex of the previous out transaction: " << tin.indexPrevTrans << std::endl;
    stream << "\tSequence number: " <<tin.seqNumber << std::endl;
    return stream;
}

