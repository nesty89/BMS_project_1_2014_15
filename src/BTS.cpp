#include "Headers.hpp"
using std::cout;
using std::endl;
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

string BTS::getGPS() {
    return this->GPS;

}

string BTS::getLocalization() {
    return this->localization;
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
    while(getline(ss, s, ',')){
        strVec.push_back(s);
    }
    this->setLongtitude(this->degreeToDec(strVec[0]));
    this->setLatitude(this->degreeToDec(strVec[1]));
}

float BTS::floatFromString(string s){
    stringstream ss(s);
    float x;
    ss >> x; 
    return x;
}