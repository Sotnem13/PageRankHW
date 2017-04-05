//
// Created by sotnem on 30.03.17.
//

#ifndef PAGERANG_URL_H
#define PAGERANG_URL_H

#include <string>

struct URL {
    static const std::string protocolDelim; //  "://"

    std::string host;
    std::string path;

    URL(std::string);
};


#endif //PAGERANG_URL_H
