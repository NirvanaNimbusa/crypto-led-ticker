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
        coins[idx].change_percent_day = i["USD"]["CHANGEPCT24HOUR"];
        coins[idx].change_percent_hour = i["USD"]["CHANGEPCTHOUR"];
        idx++;
    }
}

void CryptoCompareApi::printData() {
    for(const CoinData& i : coins) {
        std::cout << i.sym << std::endl;
        std::cout << i.price << std::endl;
    }
}

void CryptoCompareApi::saveImage() {
    unsigned char black[] = { 0, 0 , 0};

    unsigned char mainTextColour[] = { 255, 255 , 0};
    unsigned char movementTextColour[] = { 255 , 0 , 0};

    CImg<unsigned char> img(2500,32,1,3);
    img.fill(0);

    CImg<unsigned char> imgtext;
    int last_x = 0;

    for(const CoinData& i : coins) {
        imgtext.clear();

        imgtext.draw_text(last_x,0,i.sym.c_str(), mainTextColour, black,1,32);
        img.draw_text(last_x,0, i.sym.c_str(), mainTextColour, black, 1, 32);
        last_x = imgtext.width() + 5;
        imgtext.clear();

        imgtext.draw_text(last_x,0,i.sym.c_str(), mainTextColour, black,1,32);
        img.draw_text(last_x,0, ": $", mainTextColour, black, 1, 32);
        last_x = imgtext.width()-15;
        imgtext.clear();

        std::string price = std::to_string(i.price);
        imgtext.draw_text(last_x,0,price.c_str(), mainTextColour, black,1,32);
        img.draw_text(last_x,0, price.c_str(), mainTextColour, black, 1, 32);
        last_x = imgtext.width() + 5;
        imgtext.clear();

        if (i.change_percent_hour > 0) {
            movementTextColour[0] = 0;
            movementTextColour[1] = 255;
        } else {
            movementTextColour[0] = 255;
            movementTextColour[1] = 0;
        }
        std::string price_change = std::to_string(i.change_percent_hour);
        imgtext.draw_text(last_x,0,price_change.c_str(), movementTextColour, black,1,32);
        img.draw_text(last_x,0, price_change.c_str(), movementTextColour, black, 1, 32);

        last_x = imgtext.width() + 30;
    }
    img.save_pnm("./out.ppm");
}
