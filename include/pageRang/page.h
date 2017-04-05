//
// Created by sotnem on 29.03.17.
//

#ifndef PAGERANG_PAGE_H
#define PAGERANG_PAGE_H

#include <string>
#include <vector>
#include <set>


#include "pageRang/url.h"
//Queue


struct Page {
    std::string url;
    std::set<std::string> links;
    std::vector<Page*> parents;
    double pageRank;
    double exPageRank;

};

// LessThanComparable
bool operator < (const Page& lhs, const Page& rhs);

//class Page {
//public:
//    Page() = default;
//    Page(std::string);
//    Page(Page&& page) : url(page.url), parents(page.parents){}
//
//    Page& operator=(const Page& page){
//        url = page.url;
//        parents = page.parents;
//        return *this;
//    }
//
//    std::vector<std::string>& getLinks();
//    void addParent(Page*);
//
//    double getRank();
//
//    std::vector<std::string> linksOnPage;
//
//private:
//    std::string url;
//    double rank;
//    bool rankCompuded;
//
//
//    std::vector<Page*> parents;
//    static const float D; // 0.85f
//
//
//};


#endif //PAGERANG_PAGE_H
