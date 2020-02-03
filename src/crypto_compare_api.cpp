#include "crypto_compare_api.h"
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>

using json = nlohmann::json;
using namespace::std;


CryptoCompareApi::CryptoCompareApi() = default;

void CryptoCompareApi::doSomething() {
//    httplib::SSLClient cli("https://min-api.cryptocompare.com/data/pricemultifull?fsyms=BTC&tsyms=USD,EUR", 443);
//    cli.set_follow_location(true);
//    // cli.set_ca_cert_path(CA_CERT_FILE);
//    cli.enable_server_certificate_verification(true);
//
//    auto res = cli.Get("/");
//    if (res && res->status == 200) {
//        std::cout << res->body << std::endl;
//    } else {
//        std::cout << "failed" << std::endl;
//    }
}


#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "doctest.h"
TEST_CASE("we can have tests written here, to test impl. details")
{
            CHECK(true);
}
#endif
