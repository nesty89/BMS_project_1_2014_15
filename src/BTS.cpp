#include "Headers.hpp"
#include <cmath>
#include "UTM.h"

BTS::BTS(){

}

float BTS::getLongtitude(){
    return this->longtitude;
}

float BTS::getLatitude(){
    return this->latitude;
}

int BTS::getBCH() {
    return this->BCH;
}

int BTS::getCID() {
    return this->CID;
}

int BTS::getLAC() {
    return this->LAC;
}

float BTS::getDistance(){
    return this->distance;
}

string BTS::getGPS() {
    return this->GPS;

}

string BTS::getLocalization() {
    return this->localization;
}

string BTS::getULocation(){
    return this->uLoc;
}

void BTS::setULocation(string loc){
    this->uLoc = loc;
}

void BTS::setBCH(int bch) {
    this->BCH = bch;
}

void BTS::setCID(int cid) {
    this->CID = cid;
}

void BTS::setGPS(string gps) {
    this->GPS = gps;
}

void BTS::setLAC(int lac) {
    this->LAC = lac;
}

void BTS::setLocalization(string loc) {
    this->localization = loc;
}

void BTS::setLatitude(float latitude){
    this->latitude = latitude;
}

void BTS::setLongtitude(float longtitude){
    this->longtitude = longtitude;
}

void BTS::setDistance(float distance){
    this->distance = distance;
}

float BTS::degreeToDec(string degree){
    stringstream ss(degree); 
    float  x , y, z;
    std::vector<string> v;
    v.push_back("");
    int index = 0;
    for (int i = 0; i < degree.length(); i++){
        if((degree[i] - '0' >= 0 && degree[i] - '0' < 10) || degree[i] == '.'){
            v[index] += degree[i];

        } else {
            v.push_back("");
            index++;
        }
    }
    
    ss.str("");
    ss.clear();
    x = floatFromString(v[0]);
    y = floatFromString(v[1]);
    z = floatFromString(v[2]);
    
    int sign = 1;
    if (degree.find("S") !=  string::npos || degree.find("W") !=  string::npos){
        sign = -1;
    }
    return (x + y / 60 + z / 3600) * sign;
}

void BTS::computeLatitideAndLongtitude(string degrees){
    stringstream ss(degrees);
    vector<string> strVec;
    string s;
    double lat, longt;
    char *s2;
    while(getline(ss, s, ',')){
        strVec.push_back(s);
    }
    UTM::LLtoUTM((double) this->degreeToDec(strVec[0]), (double) this->degreeToDec(strVec[1]), lat, longt, s2);
    uLoc = s2;

    this->setLatitude((float) lat);
    this->setLongtitude((float) longt);
}

float BTS::floatFromString(string s){
    if(s == ""){
        return 0.0;
    }
    stringstream ss(s);
    float x;
    ss >> x; 
    return x;
}


//L_u = 10*(log10(1000*power)) - signal

float BTS::computeDistance(Ant ant) { 
    float distance = 0.0;
    float lu = 10.0 * log10(1000.0 * (float) ant.getPower()) - (float) ant.getSignal();
    float ch = 3.2 * (pow(log10(11.75 * (float) MOBILE_ANTENA), 2.0)) - 4.97;
    float rest = 69.55 + 26.16 * log10(FREQ) - 13.82 * log10((float) ant.getAntH());
    distance = lu - rest + ch;
    distance /= (44.9 - 6.55 * log10((float) ant.getAntH()));
    distance = pow(10.0, distance);
    setDistance(distance);
    return distance;
}

