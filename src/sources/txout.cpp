#include "txout.h"

TxOut::TxOut(const char *buffer, uint32_t& globalOffset)
{
    //VALUE
    uint32_t localOffset = 0;
    value = ParseUint64(buffer);
    localOffset += VALUE_SIZE;

    //SCRIPT
    varInt scriptLen = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer));
//    std::unique_ptr<char[]> tmpScript(new char[scriptLen.first]);
//    memcpy(tmpScript.get(), buffer + scriptLen.second, scriptLen.first);
//    script = std::move(tmpScript);
    localOffset += scriptLen.second;

    globalOffset += localOffset;
}


const uint64_t TxOut::GetValue() const
{
    return value;
}


std::ostream& operator<< (std::ostream& stream, const TxOut& tout)
{
    stream << "----------TxOut----------: " << std::endl;
    stream << "\t" << tout.value << std::endl;
    return stream;
}


