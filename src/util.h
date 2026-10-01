#include <iostream>

#ifdef NDEBUG
// In Release mode, this resolves to nothing and is stripped out by the compiler
#define DEBUG_LOG(msg)
#else
// In Debug mode, it prints comprehensive log details
#define DEBUG_LOG(msg)                                                                    \
    std::cerr << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " \
              << msg << std::endl
#endif