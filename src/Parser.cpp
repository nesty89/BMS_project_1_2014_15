#include "Headers.hpp"

#include <vector>
#include <sstream>
#include <iostream>
using std::vector;
using std::string;
using std::stringstream;
using std::getline;

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
void Parser::clearStringStream(){
    ss.str();
    ss.clear();
}
