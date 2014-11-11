#include "Headers.hpp"

BTS::BTS(){

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