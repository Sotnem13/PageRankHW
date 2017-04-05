#include <iostream>
#include <fstream>
#include <chrono>

#include "pageRang/net_manager.h"
#include "pageRang/net_graph.h"


NetGraph ng;
//std::string link{"http://cppreference.com"};
std::string link{"http://stackoverflow.com"};


void downloadPages() {
    ng.addToQueue(link);
    ng.downloadPagesAndGetLinks(100);
}
void saveMatrix(){
    std::ofstream file("output_matrix.txt");
    ng.printMatrix(file);
}

void calcPR(){
    using namespace std::chrono;
    ng.preparePR();

    high_resolution_clock clock;
    auto begin = clock.now();

    ng.calcPR();

    auto elapsedTime = duration_cast<duration<double> >(clock.now() - begin);

    ng.sortAndPrint(std::cout);
    std::cout << "calcPR took: " << elapsedTime.count() << std::endl;
    std::ofstream file("calcPR.txt");
    ng.sortAndPrint(file);
}
void calcExPR(){

    using namespace std::chrono;

    ng.preparePR();

    high_resolution_clock clock;
    auto begin = clock.now();

    ng.calcExPR();

    auto elapsedTime = duration_cast<duration<double> >(clock.now() - begin);
    std::cout << "calcExPR took: " << elapsedTime.count() << std::endl;

    std::ofstream file("calcExPR.txt");
    ng.sortAndPrint(file);
}
void calcParallelExPR(){
    using namespace std::chrono;

    ng.preparePR();
    ng.prepareParallel();

    high_resolution_clock clock;
    auto begin = clock.now();

    ng.calcParallelExPR();

    auto elapsedTime = duration_cast<duration<double> >(clock.now() - begin);
    std::cout << "calcParallelExPR took: " << elapsedTime.count() << std::endl;
}

int main() {

    downloadPages();
    saveMatrix();


    calcPR();
    calcExPR();
    calcParallelExPR();


    return 0;
}

