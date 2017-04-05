//
// Created by sotnem on 30.03.17.
//

#ifndef PAGERANG_NET_MANAGER_H
#define PAGERANG_NET_MANAGER_H


#include <string>
#include <vector>
#include <functional>

#include <curl/curl.h>

#include "pageRang/url.h"


class NetManager {
    using ThresholdFunc = std::function<bool(std::string)>;

public:
    NetManager();
    ~NetManager();
    std::string getBody(std::string url);
    std::vector<std::string> getLinksOnPage(URL pageUrl);
    std::vector<std::string> getLinksOnPage(URL pageUrl, ThresholdFunc);

private:
    CURL *curl;
    std::string buffer;
    static const std::string hrefAttr;
};


#endif //PAGERANG_NET_MANAGER_H
