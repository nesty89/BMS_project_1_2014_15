#include "Headers.hpp"
#include <cmath>

#define ICONV 3
using std::cout;
using std::endl;


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
    btsVector = parser->filterUnusedBts(btsVector, anthVector);
    
    for(int i = 0; i < anthVector.size(); i++){
        for (int j = 0; j < btsVector.size(); j++){
            if(anthVector[i].getCID() == btsVector[j].getCID()){
                btsVector[j].computeDistance(anthVector[i]);
            }
        }
    }

    Computation *cp = new Computation();
    cp->setAntVect(anthVector);
    cp->setBtsVect(btsVector);
    cp->compute();

    FileWriter *fw = new FileWriter("out.txt");
    float gpsw = 12.123456;
    float gpsh = gpsw;
    fw->writeLine(fw->prepareGPSLink(gpsw, gpsh), true);
    fw->closeFile();
    return 0;
}
