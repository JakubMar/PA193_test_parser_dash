#include "common.h"
#include <ostream>

const uint32_t VALUE_SIZE = 8;

class TxOut
{
private:
    uint64_t value;
    //std::unique_ptr<char[]> script;
public:
    TxOut(const char* buffer, uint32_t& globalOffset);



    friend std::ostream& operator<< (std::ostream& stream, const TxOut& tout);
};

