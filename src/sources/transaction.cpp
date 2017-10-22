#include "transaction.h"

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
