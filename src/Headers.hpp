#ifndef HEADERS_HPP
#define HEADERS_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::stringstream;

// m
#define MOBILE_ANTENA 1.2f
// MHz
#define FREQ 900

class FileReader {
public:
    FileReader(string name);
    string GetLine();
    void setFileName(string fileName);
    bool isEnd();
    void initNew(string name);
    void closeFile();
private:
    string fileName;
    bool end;
    std::ifstream is;
};

class Ant{
public:
    Ant();
    void setLAC(int lac);
    void setCID(int cid);
    void setRSSI(int rssi);
    void setSignal(int sig);
    void setAntH(int ah);
    void setPower(int power);
    int getLAC();
    int getCID();
    int getRSSI();
    int getSignal();
    int getAntH();
    int getPower();

private:
    int LAC;
    int CID;
    int RSSI;
    int Signal;
    int AntH;
    int Power; // wats
};

class BTS{
public:
    BTS();
    void setCID(int cid);
    void setLAC(int lac);
    void setBCH(int bch);
    void setLocalization(string loc);
    void setGPS(string gps);
    int getCID();
    int getLAC();
    int getBCH();
    string getLocalization();
    string getGPS();
private:
    int CID;
    int LAC;
    int BCH;
    string localization;
    string GPS;
};

class Parser{
public:
    vector<string> parseLine(string str);
    BTS getBTSFromVect(vector<string> v);
    Ant getAntFromVect(vector<string> v);
    Parser();
private:
    stringstream ss;
    int getIntFromString(string str);
    void clearStringStream();

};


#endif