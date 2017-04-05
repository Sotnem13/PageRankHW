//
// Created by sotnem on 02.04.17.
//


//#include <parallel/for_each.h>
//#include <parallel/par_loop.h>
//#include <ppl.hh>
#include <tbb/parallel_for.h>

#include <pageRang/net_graph.h>

NetGraph::~NetGraph(){
    if(values != nullptr) delete[] values;
};

const double NetGraph::D = 0.85;

void NetGraph::addToQueue(std::string link){
    queue.push(link);
}
void NetGraph::downloadPagesAndGetLinks(int pageCount) {
    std::cout << "Downloading";
    while (!queue.empty() && pages.size() < pageCount){
        auto link = std::move(queue.front());
        queue.pop();
        if( pages.find(link) != pages.end()) continue;

        auto links = std::move(nm.getLinksOnPage(link));

        pages.insert({link,Page{link}});

        auto& page = pages[link];
        for( auto &l : links ){
            auto p = pages.find(l);
            page.links.insert(l);
            if( p == pages.end() ){
                queue.push(l);
            } else {
                p->second.parents.push_back(&pages[link]);
            }
        }

    }
    std::cout << " done" << std::endl;
}

void NetGraph::printMatrix(std::ostream& out){

    auto i = pages.begin();
    while( i != pages.end() ) {
        auto j = pages.begin();
        auto& page = i->second;
        while( j != pages.end() ) {
            auto& link = j->first;
            auto it = page.links.find(link);
            auto o = (it != page.links.end());
            out << o << ' ';
            ++j;
        }
        out << page.url << std::endl;
        ++i;
    }

}
void NetGraph::sortAndPrint(std::ostream& out) {
    set.clear();
    for( auto &p : pages) set.insert(p.second);

    auto rit = set.crbegin();
    while(rit != set.crend()) {
        out << rit->pageRank << ":\t" << rit->url << std::endl;
        ++rit;
    }

};

void NetGraph::preparePR(){
    double n = pages.size();
    for( auto &p : pages ) {
        p.second.pageRank = 1.0 / n;
    }
}

void NetGraph::calcPR(){
    double n = pages.size();

    for( int i = 0; i < 100; ++i ) {
        for( auto &p : pages ) {
            double sum = 0.0;
            for ( auto parent : p.second.parents )  {
                sum += parent->pageRank / parent->links.size();
            }
            p.second.pageRank = (1 - D) / n + D*sum;
        }
    }
}

void NetGraph::calcExPR(){
    for (int k = 0; k < 100; k++) {
        for (auto &p : pages) {
            auto &page = p.second;
            double pageRank = 0;
            for (auto &parent : page.parents) {
                pageRank += 1.0 / parent->links.size();
            }
            page.exPageRank = pageRank;
        }
        normalize();
    }
}
void NetGraph::normalize(){
    for(auto &p : pages) {
        p.second.pageRank = p.second.exPageRank;
    }
}

void NetGraph::prepareParallel(){
    if(values != nullptr) delete[] values;
    values = new Page*[pages.size()];
    auto p = pages.begin();
    for (int i = 0; i < pages.size(); ++p,++i) {
        values[i] = &p->second;
    }
}

void NetGraph::calcParallelExPR(){

    for (int k = 0; k < 100; k++) {
        tbb::parallel_for(size_t(0), pages.size(), [&](int i) {
                auto &page = *values[i];
                double pageRank = 0;
                for (auto &parent : page.parents) {
                    pageRank += 1.0 / parent->links.size();
                }
                page.exPageRank = pageRank;
        });
        normalize();
    }
}
