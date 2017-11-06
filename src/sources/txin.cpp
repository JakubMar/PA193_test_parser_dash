#include "txin.h"
#include "invalidtransactionsizeexcepion.h"
#include "invalidscriptsizeexcepion.h"

TxIn::TxIn(const char *buffer, uint32_t &globalOffset, size_t &unread_size)
{
    uint32_t localOffset = 0;

    //HASH_PREV_TRANS
    if(unread_size < HASH_SIZE)
        throw InvalidTransactionSizeException("TxIn: invalid read of Hash");
    memcpy(&hashPrevTrans, buffer, HASH_SIZE);
    localOffset += HASH_SIZE;
    unread_size -= HASH_SIZE;

    //INDEX_PREV_TRANS
    if(unread_size < INDEX_SIZE)
        throw InvalidTransactionSizeException("TxIn: invalid read of Index");
    indexPrevTrans = ParseUint32(buffer);
    localOffset += INDEX_SIZE;
    unread_size -= INDEX_SIZE;

    //SCRIPT OFFSETS
    varInt scriptLen = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset), unread_size);
    localOffset += scriptLen.second;
    unread_size -= scriptLen.second;
    if(unread_size < scriptLen.first)
        throw InvalidScriptSizeException();
    scriptOffsets = offsets(localOffset, localOffset + scriptLen.first);

    localOffset += scriptLen.first;
    unread_size -= scriptLen.first;

    //SEQUENCE NUMBER
    if(unread_size < SEQUENCE_NUM_SIZE)
        throw InvalidTransactionSizeException("TxIn: invalid read of Sequence");
    seqNumber = ParseUint32(buffer + localOffset);
    localOffset += SEQUENCE_NUM_SIZE;
    unread_size -= SEQUENCE_NUM_SIZE;

    globalOffset += localOffset;
}


uint32_t TxIn::GetSeqNumber() const
{
    return seqNumber;
}

uint256 TxIn::GetHashPrevTrans() const{
    return hashPrevTrans;
}


std::ostream& operator<< (std::ostream& stream, const TxIn& tin)
{
    stream << "----------TxIn----------: " << std::endl;
    stream << "\tPrev tx hash: " << tin.hashPrevTrans.GetHex() << std::endl;
    stream << "\tPrev tx index: " << tin.indexPrevTrans << std::endl;
    stream << "\tSequence number: " <<tin.seqNumber << std::endl;
    return stream;
}

