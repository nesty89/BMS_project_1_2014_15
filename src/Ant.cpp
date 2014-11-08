#include "Headers.hpp"

Ant::Ant(){}

void Ant::setLAC(int lac){
    LAC = lac;
}

void Ant::setCID(int cid){
    CID = cid;
}
void Ant::setRSSI(int rssi){
    RSSI = rssi;
}
void Ant::setSignal(int sig){
    Signal = sig;
}
void Ant::setAntH(int ah){
    AntH = ah;
}
void Ant::setPower(int power){
    Power = power;
}
int Ant::getLAC(){
    return LAC;
}
int Ant::getCID(){
    return CID;
}
int Ant::getRSSI(){
    return RSSI;
}
int Ant::getSignal(){
    return Signal;
}
int Ant::getAntH(){
    return AntH;
}
int Ant::getPower(){
    return Power;
}