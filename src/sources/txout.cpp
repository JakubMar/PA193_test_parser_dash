#include "txout.h"

std::ostream& operator<< (std::ostream& stream, const TxOut& tout)
{
    stream << "----------TxOut----------: " << std::endl;
    stream << "\t" << tout.value << std::endl;
    return stream;
}
