#include "txin.h"
#include "txout.h"
#include <vector>
class Transaction
{
private:
    uint32_t version;
    std::vector<TxIn> inTrans;
    std::vector<TxOut> outTrans;
    uint32_t lockTime;

public:
    friend std::ostream& operator<<(std::ostream& stream, const Transaction& t);
};


