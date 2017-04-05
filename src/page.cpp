//
// Created by sotnem on 30.03.17.
//

#include "pageRang/net_manager.h"
#include "pageRang/page.h"

bool operator < (const Page& lhs, const Page& rhs) { return lhs.pageRank < rhs.pageRank; }

//const float Page::D = 0.85f;

//Page::Page(std::string link):url(link){

//}

//double Page::getRank(){
//    if(rankCompuded)
//        return rank;
//    rank = 1 - D;
//    for( auto p : parents ){
//        rank += D*(p->getRank()/p->getLinks().size());
//    }
//    rankCompuded = true;
//    return  rank;
//}

//std::vector<std::string>& Page::getLinks() {

//    return nullptr;
//};
//void Page::addParent(Page* parent){
//    parents.push_back(parent);
//}
