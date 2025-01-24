
#include <cstdint>

using SecurityId = uint64_t;
using SharesOutstanding = uint64_t;


class Security {

    public:

        Security(SecurityId);

    private:
        SecurityId securityId_;
        SharesOutstanding SharesOutstanding_;

};