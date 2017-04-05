//
// Created by sotnem on 30.03.17.
//

#include <pageRang/url.h>
#include <sstream>
#include <cstring>

const std::string URL::protocolDelim = "//";

URL::URL(std::string link){
    std::stringstream ss;
    auto p = link.find(protocolDelim);
    if( p == std::string::npos )
        p = 0;
    else
        p += protocolDelim.length();

    auto firstSlash = link.find("/",p);
    if(firstSlash == std::string::npos) {
        host = link.substr(0);
        path = "/";
    } else {
        host = link.substr(0, firstSlash);
        path = link.substr(firstSlash);
    }
}