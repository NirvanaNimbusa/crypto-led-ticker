// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

#include <iostream>
#include "version.h"
#include "crypto_compare_api.h"

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */

int main() {
  std::cout << "Crypto LED Ticker v"
            << PROJECT_VERSION_MAJOR
            << "."
            << PROJECT_VERSION_MINOR
            << "."
            << PROJECT_VERSION_PATCH
            << "."
            << PROJECT_VERSION_TWEAK
            << std::endl;

  CryptoCompareApi c = CryptoCompareApi("BTC,BCH,LTC,BSV,ETC,XRP");
  c.parseJson(c.doRequest());
  c.printData();

  return 0;
}
