#include "transaction.h"

void Transaction::setVersion(const uint32_t &value)
{
    version = value;
}


void Transaction::setInTrans(const std::vector<TxIn> &value)
{
    inTrans = value;
}


void Transaction::setOutTrans(const std::vector<TxOut> &value)
{
    outTrans = value;
}


void Transaction::setLockTime(const uint32_t &value)
{
    lockTime = value;
}


void Transaction::setBeginEndOffsets(const offsets &value)
{
    beginEndOffsets = value;
}


Transaction::Transaction(const char *buffer, uint32_t &globalOffset) : beginEndOffsets(offsets(0,0))
{
    uint32_t localOffset = 0;

    version = ParseUint32(buffer);
    localOffset += VERSION_SIZE;

    varInt txInCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset));
    localOffset += txInCount.second;
    for(size_t i = 0; i < txInCount.first; ++i)
    {
        inTrans.emplace_back(TxIn(buffer+localOffset, localOffset));
    }

    varInt txOutCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset));
    localOffset += txOutCount.second;
    for(size_t i = 0; i < txOutCount.first; ++i)
    {
        outTrans.emplace_back(TxOut(buffer+localOffset, localOffset));
    }

    lockTime = ParseUint32(buffer);
    localOffset += TIME_SIZE;

    beginEndOffsets = offsets(globalOffset, localOffset);
    globalOffset += localOffset;
}


const offsets Transaction::GetOffsets() const
{
    return beginEndOffsets;
}


uint32_t Transaction::GetVersion() const
{
    return version;
}


const std::vector<TxIn>& Transaction::GetInputs() const
{
    return inTrans;
}


const std::vector<TxOut>& Transaction::GetOutputs() const
{
    return outTrans;
}


uint32_t Transaction::GetLockTime() const
{
    return lockTime;
}

std::ostream& operator<<(std::ostream& stream, const Transaction& t)
{
    stream << "-------TRANSACTION-------: " << std::endl;
    stream << "TxIn:" << std::endl;
    for(auto& it : t.inTrans)
    {
        stream << "/t" << it << std::endl;
    }

    stream << "TxOut:" << std::endl;
    for(auto& it : t.outTrans)
    {
        stream << "/t" << it << std::endl;
    }

    return stream;
}

