#include "common.h"
#include <ostream>

class TxIn
{
private:
    uint256 hashPrevTrans;
    uint32_t indexPrevTrans;
    std::unique_ptr<char[]> script;
    uint32_t seqNumber;
public:
    friend std::ostream& operator<< (std::ostream& stream, const TxIn& tin);
};

