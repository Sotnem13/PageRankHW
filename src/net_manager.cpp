//
// Created by sotnem on 30.03.17.
//


#include <sstream>
#include <iostream>

#include "pageRang/net_manager.h"

const std::string NetManager::hrefAttr{"href"};

static size_t write_data(char *data, size_t size, size_t nmemb, std::string *writerData ){
    size_t segsize = (size * nmemb);
    writerData->append(data, size*nmemb);
    return segsize;
}


NetManager::NetManager() {
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
}

NetManager::~NetManager() {
    curl_easy_cleanup(curl);
}

std::string NetManager::getBody(std::string url){
    buffer.clear();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl);
    return buffer;
}
std::vector<std::string> NetManager::getLinksOnPage(URL pageUrl){
    return getLinksOnPage(pageUrl,[](std::string link){
        return link.find_first_of("?#") == std::string::npos;
    });
}

std::vector<std::string> NetManager::getLinksOnPage(URL pageUrl, ThresholdFunc linkThreshold ){

    auto url = pageUrl.host + pageUrl.path;
    auto responseBody = getBody(url);

    std::vector<std::string> result;
    auto aTag    = responseBody.find("<a");
    auto aTagEnd = responseBody.find(">",aTag);
    auto hrefPos = responseBody.find(hrefAttr,aTag);

    while( hrefPos != std::string::npos ){
        if( hrefPos > aTagEnd) {
            aTag    = responseBody.find("<a",aTagEnd);
            aTagEnd = responseBody.find(">",aTag);
            hrefPos = responseBody.find(hrefAttr,aTag);
            continue;
        }
        auto firstQuotePos  = responseBody.find_first_of("'\"",hrefPos);
        auto secondQuotePos = responseBody.find_first_of(responseBody[firstQuotePos],firstQuotePos+1);
        auto linkLength     = secondQuotePos - firstQuotePos - 1;

        aTag    = responseBody.find("<a",aTagEnd);
        aTagEnd = responseBody.find(">",aTag);
        hrefPos = responseBody.find(hrefAttr,aTag);

        if( linkLength == 0  ) continue; // ignore empty links
        auto link = responseBody.substr(firstQuotePos+1,linkLength);
        URL u(link);
        if(u.host.empty()) link = pageUrl.host + u.path;
        if( linkThreshold(link) ) {
            result.push_back(link);
        }
    }

    return result;
}

