#include "Headers.hpp"
#include <cmath>

#define ICONV 3
using std::cout;
using std::endl;


//float Ch = 3.2 * (pow(log10(11.75 * MOBILE_ANTENA), 2.0)) - 4.97;
// latitude -- W -> E
// longtitude -- N -> S     

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
                bts.computeLatitideAndLongtitude(bts.getGPS()); 
                btsVector.push_back(bts);
            }
        }
        first = false;
    }
    btsFile->closeFile();

    anthVector = parser->filterSimilarAntPoint(btsVector, anthVector);
  
    FileWriter *fw = new FileWriter("out.txt");
    float gpsw = 12.123456;
    float gpsh = gpsw;
    fw->writeLine(fw->prepareGPSLink(gpsw, gpsh), true);
    fw->closeFile();
    return 0;
}

        