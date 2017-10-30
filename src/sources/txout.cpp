#include "txout.h"
#include "invalidtransactionsizeexcepion.h"
#include "invalidscriptsizeexcepion.h"

TxOut::TxOut(const char *buffer, uint32_t& globalOffset, size_t& unread_size)
{
    //VALUE
    if(unread_size < VALUE_SIZE)
        throw InvalidTransactionSizeException("TxOut: invalid read of Value");
    uint32_t localOffset = 0;
    value = ParseUint64(buffer);
    localOffset += VALUE_SIZE;
    unread_size -= VALUE_SIZE;

    //SCRIPT
    varInt scriptLen = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset), unread_size);
    localOffset += scriptLen.second;
    unread_size -= scriptLen.second;

    if(unread_size < scriptLen.first)
    {
        throw InvalidScriptSizeException();
    }

//    std::unique_ptr<char[]> tmpScript(new char[scriptLen.first]);
//    memcpy(tmpScript.get(), buffer + localOffset, scriptLen.first);
//    script = std::move(tmpScript);

    localOffset += scriptLen.first;
    unread_size -= scriptLen.first;

    globalOffset += localOffset;
}


uint64_t TxOut::GetValue() const
{
    return value;
}


std::ostream& operator<< (std::ostream& stream, const TxOut& tout)
{
    stream << "----------TxOut----------: " << std::endl;
    stream << "\tValue: " << tout.value / 100000000 << std::endl;
    return stream;
}


