#include "common.h"
#include <ostream>

class TxOut
{
private:
    uint64_t value;
    std::unique_ptr<char[]> script;
public:
    friend std::ostream& operator<< (std::ostream& stream, const TxOut& tout);
};

