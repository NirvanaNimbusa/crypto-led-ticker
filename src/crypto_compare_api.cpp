#include "crypto_compare_api.h"

CryptoCompareApi::CryptoCompareApi(string cur)  {
    currencies = std::move(cur);
}

std::string CryptoCompareApi::doRequest() {
    httplib::SSLClient cli("min-api.cryptocompare.com", 443);
    cli.set_follow_location(true);
    cli.set_ca_cert_path(CA_CERT_FILE);
    cli.enable_server_certificate_verification(true);

    std::cout << "Cur: " << currencies << std::endl;
    string path = "/data/pricemultifull?fsyms=" + currencies + "&tsyms=USD";
    auto res = cli.Get(path.c_str());
    if (res && res->status == 200) {
        return res->body;
    }
    return "";
}

void CryptoCompareApi::parseJson(const std::string& input)  {
    auto x = json::parse(input);
    std::stringstream ss;
    int idx = 0;
    for (const auto& i : x["RAW"]) {
        coins[idx].sym = i["USD"]["FROMSYMBOL"];
        coins[idx].price = i["USD"]["PRICE"];
        idx++;
    }
}

void CryptoCompareApi::printData() {
    for(const auto& i : coins) {
        std::cout << i.sym << std::endl;
        std::cout << i.price << std::endl;
    }
}

void CryptoCompareApi::saveImage() {
    CImg<unsigned char> image("lena.jpg"), visu(500,400,1,3,0);
}

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "doctest.h"
TEST_CASE("we can have tests written here, to test impl. details")
{
            CHECK(true);
}
#endif
