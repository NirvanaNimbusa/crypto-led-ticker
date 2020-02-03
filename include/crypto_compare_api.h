#pragma once
// #define CPPHTTPLIB_OPENSSL_SUPPORT

/**
 * This is a dummy class to demonstrate features of the boiler plate.
 */
class CryptoCompareApi {
public:

    /**
     * Default constructor for Dummy (does nothing).
     */
    CryptoCompareApi();
    /**
     * Returns a bool.
     * @return Always True.
     */
    static void doSomething();
};


#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "doctest.h"
TEST_CASE("we can have tests in headers if we want")
{
//    CryptoCompareApi d;
//    CHECK(d.doSomething());
}
#endif
