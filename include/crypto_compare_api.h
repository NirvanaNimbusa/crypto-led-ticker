#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CA_CERT_FILE "../data/ca-bundle.crt"

#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <CImg.h>
using namespace cimg_library;

using json = nlohmann::json;
using namespace::std;

/**
 * This is a dummy class to demonstrate features of the boiler plate.
 */
class CryptoCompareApi {
private:
    string currencies;

    struct CoinData {
        std::string sym;
        float price;
        float change_percent_hour;
        float change_percent_day;
    } coins[6];
public:
    explicit CryptoCompareApi(string cur);
    std::string doRequest();
    void parseJson(const string& input);
    void printData();

    void saveImage();
};



#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "doctest.h"
TEST_CASE("we can have tests in headers if we want")
{
//    CryptoCompareApi d;
//    CHECK(d.doSomething());
}
#endif
