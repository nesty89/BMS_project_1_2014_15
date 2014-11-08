#include "Headers.hpp"
#include <cmath>


using std::cout;
using std::endl;



int main(int argc, char **argv){
    FileReader *btsFile  = new FileReader("bts.csv");
    FileReader *inputFile  = new FileReader(argv[1]);

    Parser *parser = new Parser();
    vector<BTS> btsVector;
    vector<Ant> anthVector;
    float Ch = 3.2 * (pow(log10(11.75 * MOBILE_ANTENA), 2.0)) - 4.97;
    std::cout << Ch << std::endl << std::endl;
    std::string s;
    while(!btsFile->isEnd() || !inputFile->isEnd()) {
        s = btsFile->GetLine();
        if (!btsFile->isEnd()) {
            BTS bts = parser->getBTSFromVect(parser->parseLine(s));
            btsVector.push_back(bts);
        }

        s = inputFile->GetLine();
        if(!inputFile->isEnd()){
            Ant ant =  parser->getAntFromVect(parser->parseLine(s));
            anthVector.push_back(ant);
        }
    }

    btsVector.erase(btsVector.begin());
    anthVector.erase(anthVector.begin());

    cout << btsVector.size() << endl;
    cout << anthVector.size() << endl;
    return 0;
}

// 49°13'33.97"N,16°35'35.64"E
// 49°13'33.97"N,16°35'35.64"E
// 49°13'33.97"N,16°35'35.64"E
// 49°13'11.81"N,16°36'25.26"E
// 49°13'42.18"N,16°34'53.07"E
// 49°13'33.97"N,16°35'35.64"E
// 49°13'11.81"N,16°36'25.26"E
