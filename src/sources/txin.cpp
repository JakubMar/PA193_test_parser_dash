#include "txin.h"


std::ostream& operator<< (std::ostream& stream, const TxIn& tin)
{
    stream << "----------TxIn----------: " << std::endl;
    stream << "\tHash of the previous out transaction: " << tin.hashPrevTrans.GetHex() << std::endl;
    stream << "\tIndex of the previous out transaction: " << tin.indexPrevTrans << std::endl;
    stream << "\tSequence number: " <<tin.seqNumber << std::endl;
    return stream;
}
