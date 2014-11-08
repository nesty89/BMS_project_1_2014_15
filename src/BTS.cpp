#include "Headers.hpp"

BTS::BTS(){

}


int BTS::getBCH() {
    return BCH;
}

int BTS::getCID() {
    return CID;
}

int BTS::getLAC() {
    return LAC;
}

string BTS::getGPS() {
    return GPS;

}

string BTS::getLocalization() {
    return localization;
}

void BTS::setBCH(int bch) {
    BCH = bch;
}

void BTS::setCID(int cid) {
    CID = cid;
}

void BTS::setGPS(string gps) {
    GPS = gps;
}

void BTS::setLAC(int lac) {
    LAC = lac;
}

void BTS::setLocalization(string loc) {
    localization = loc;
}