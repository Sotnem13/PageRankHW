//
// Created by sotnem on 02.04.17.
//

#ifndef PAGERANG_GRAPH_H
#define PAGERANG_GRAPH_H

#include <unordered_map>
#include <queue>
#include <iostream>

#include "pageRang/page.h"
#include "pageRang/url.h"
#include "pageRang/net_manager.h"


class NetGraph {
public:
    NetGraph() = default;
    ~NetGraph();
    void addToQueue(std::string);
    void downloadPagesAndGetLinks(int);


    void sortAndPrint(std::ostream&);
    void printMatrix(std::ostream&);

    void calcPR();
    void calcExPR();
    void calcParallelExPR();
    void preparePR();

    void prepareParallel();

    static const double D;

private:
    void normalize();

    std::set<Page> set;
    Page **values;
    std::queue<std::string> queue;
    std::unordered_map<std::string,Page> pages;
    NetManager nm;
};


#endif //PAGERANG_GRAPH_H
