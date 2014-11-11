#include "Headers.hpp"

Ant::Ant(){}

void Ant::setLAC(int lac){
    this->LAC = lac;
}

void Ant::setCID(int cid){
    this->CID = cid;
}
void Ant::setRSSI(int rssi){
    this->RSSI = rssi;
}
void Ant::setSignal(int sig){
    this->Signal = sig;
}
void Ant::setAntH(int ah){
    this->AntH = ah;
}
void Ant::setPower(int power){
    this->Power = power;
}
int Ant::getLAC(){
    return this->LAC;
}
int Ant::getCID(){
    return this->CID;
}
int Ant::getRSSI(){
    return this->RSSI;
}
int Ant::getSignal(){
    return this->Signal;
}
int Ant::getAntH(){
    return this->AntH;
}
int Ant::getPower(){
    return this->Power;
}