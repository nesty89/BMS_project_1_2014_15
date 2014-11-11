#include "Headers.hpp"

#include <vector>
#include <sstream>
#include <iostream>
using std::vector;
using std::string;
using std::stringstream;
using std::getline;

using namespace std;
Parser::Parser(){};

vector<string> Parser::parseLine(string str) {
    clearStringStream();
    ss << str;
    vector<string> v;
    string s;
    while(getline(ss, s, ';')){
        v.push_back(s);
    }
    return v;
}

int Parser::getIntFromString(string str){
    int value;
    clearStringStream();
    ss << str;
    ss >> value;
    return value;
}


BTS Parser::getBTSFromVect(vector<string> v){    
    BTS bts;
    bts.setCID(getIntFromString(v[0]));
    bts.setLAC(getIntFromString(v[1]));
    bts.setBCH(getIntFromString(v[2]));
    bts.setLocalization(v[3]);
    bts.setGPS(v[4]);
    return bts;
}

Ant Parser::getAntFromVect(vector<string> v){
    Ant anth;
    anth.setLAC(getIntFromString(v[0]));
    anth.setCID(getIntFromString(v[1]));
    anth.setRSSI(getIntFromString(v[2]));
    anth.setSignal(getIntFromString(v[3]));
    anth.setAntH(getIntFromString(v[4]));
    anth.setPower(getIntFromString(v[5]));  

    return anth;
}

// todo : presunout do jine tridy - filter
vector<Ant> Parser::filterSimilarAntPoint(vector<BTS> bts, vector<Ant> ant){
    vector<string> gpsVect;
    vector<Ant> a;
    for ( int i = 0; i < ant.size(); i++){
        Ant an = ant[i];
        for ( int j = 0; j < bts.size(); j++){
            BTS b = bts[j];
            if( bts[j].getCID() == ant[i].getCID()){
                gpsVect.push_back(bts[j].getGPS());
            }
        }
    }
    // TOOD: promyslet jeste check dle popisu lokace
    for ( int i = 0; i < gpsVect.size(); i++){
        for(int j = 0; j < gpsVect.size(); j++){
            if(gpsVect[i] == "") continue;
            if(gpsVect[i] == gpsVect[j] && i != j){
                if(ant[i].getRSSI() > ant[j].getRSSI()){
                    gpsVect[j] = "";
                } else if (ant[i].getRSSI() < ant[j].getRSSI()){
                    gpsVect[i] = "";
                } else {
                    if(ant[i].getSignal() < ant[j].getSignal() ){
                        gpsVect[i] = "";
                    } else {
                        gpsVect[j] = "";
                    } 
                }
            }
        }
    }

    for(int i = 0; i < gpsVect.size(); i++){
        if(gpsVect[i] != ""){
            a.push_back(ant[i]);
        }
    }
    return a;
}

bool Parser::checkBtsNeeded(BTS bts, vector<Ant> ant){
    for (int i = 0; i < ant.size(); i++){
        if(ant[i].getCID() == bts.getCID()){
            return true;
        }
    }
    return false;
}

void Parser::clearStringStream(){
    ss.str("");
    ss.clear();
}
