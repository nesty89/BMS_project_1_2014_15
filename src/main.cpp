#include "Headers.hpp"
#include <cmath>


using std::cout;
using std::endl;

//float Ch = 3.2 * (pow(log10(11.75 * MOBILE_ANTENA), 2.0)) - 4.97;
    

int main(int argc, char **argv){
    FileReader *btsFile  = new FileReader("bts.csv");
    FileReader *inputFile  = new FileReader(argv[1]);

    Parser *parser = new Parser();
    vector<BTS> btsVector;
    vector<Ant> anthVector;
    std::string s;
    bool first = true;
    while(!inputFile->isEnd()){
        s = inputFile->GetLine();
        if(!inputFile->isEnd() && !first){
            Ant ant = parser->getAntFromVect(parser->parseLine(s));
            anthVector.push_back(ant);
        }
        first = false;
    } 
    inputFile->closeFile();
    first = true;
    while(!btsFile->isEnd() ) {
        s = btsFile->GetLine();
        if (!btsFile->isEnd() && !first) {
            BTS bts = parser->getBTSFromVect(parser->parseLine(s));
            if(parser->checkBtsNeeded(bts, anthVector)){
                btsVector.push_back(bts);
            }
        }
        first = false;
    }
    btsFile->closeFile();

    anthVector =  parser->filterSimilarAntPoint(btsVector, anthVector);
  
    FileWriter *fw = new FileWriter("out.txt");
    float gpsw =  123.123456;
    float gpsh = gpsw;
    fw->writeLine(fw->prepareGPSLink(gpsw, gpsh), false);
    fw->closeFile();
    return 0;
}

// 49°13'33.97"N,16°35'35.64"E
// 49°13'33.97"N,16°35'35.64"E
// 49°13'33.97"N,16°35'35.64"E
// 49°13'11.81"N,16°36'25.26"E
// 49°13'42.18"N,16°34'53.07"E
// 49°13'33.97"N,16°35'35.64"E
// 49°13'11.81"N,16°36'25.26"E
        