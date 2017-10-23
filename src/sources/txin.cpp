#include "txin.h"
const uint32_t INDEX_SIZE = 4;
const uint32_t SEQUENCE_NUM_SIZE = 4;

TxIn::TxIn(const char *buffer, uint32_t &globalOffset)
{
    uint32_t localOff = 0;

    //HASH_PREV_TRANS
    memcpy(&hashPrevTrans, buffer, HASH_SIZE);
    localOff += HASH_SIZE;

    //INDEX_PREV_TRANS
    indexPrevTrans = ParseUint32(buffer);
    localOff += INDEX_SIZE;

    //SCRIPT
    varInt scriptLen = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer));
    localOff += scriptLen.second;
    //std::unique_ptr<char[]> tmpScript(new char[scriptLen.first]);

    //memcpy(tmpScript.get(), buffer + localOff, scriptLen.first);

    //script = std::move(tmpScript);
    localOff += scriptLen.second;

    //SEQUENCE NUMBER
    seqNumber = ParseUint32(buffer);
    localOff += SEQUENCE_NUM_SIZE;

    globalOffset += localOff;
}

std::ostream& operator<< (std::ostream& stream, const TxIn& tin)
{
    stream << "----------TxIn----------: " << std::endl;
    stream << "\tHash of the previous out transaction: " << tin.hashPrevTrans.GetHex() << std::endl;
    stream << "\tIndex of the previous out transaction: " << tin.indexPrevTrans << std::endl;
    stream << "\tSequence number: " <<tin.seqNumber << std::endl;
    return stream;
}

