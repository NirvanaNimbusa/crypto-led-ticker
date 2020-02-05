#include <iostream>
#include "version.h"
#include "crypto_compare_api.h"

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

  CryptoCompareApi c = CryptoCompareApi("BTC,BCH,LTC,BSV,ETH,XRP");
  c.parseJson(c.doRequest());
  c.saveImage();
}
