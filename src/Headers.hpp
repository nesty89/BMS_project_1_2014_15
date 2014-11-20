#ifndef HEADERS_HPP
#define HEADERS_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

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
    void setLatitude(float latitude);
    void setLongtitude(float longtitude);
    void setDistance(float distance);
    int getCID();
    int getLAC();
    int getBCH();
    float getDistance();
    string getLocalization();
    string getGPS();
    float getLatitude();
    float getLongtitude();
    float degreeToDec(string degree);
    void computeLatitideAndLongtitude(string degrees);
    float computeDistance(Ant ant);

private:
    int CID;
    int LAC;
    int BCH;
    string localization;
    string GPS;
    float latitude;
    float longtitude;
    float distance;// km
    float floatFromString(string s);

};

class Parser{
public:
    vector<string> parseLine(string str);
    BTS getBTSFromVect(vector<string> v);
    Ant getAntFromVect(vector<string> v);
    vector<Ant> filterSimilarAntPoint(vector<BTS> bts, vector<Ant> ant);
    bool checkBtsNeeded(BTS bts, vector<Ant> ant);
    vector<BTS> filterUnusedBts(vector<BTS> btsVect, vector<Ant> antVect);
    Parser();
private:
    stringstream ss;
    int getIntFromString(string str);
    void clearStringStream();

};

class FileWriter{
public:
    FileWriter(string name);
    void writeLine(string line, bool endl);
    void writeLine(string line);
    string prepareGPSLink(float gpsWidth, float gpsHeight);
    string parseGPS(float gps);
    void closeFile();
private:
    string fileName;
    std::ofstream os;

};

class Dist{
public:
    Dist();
    Dist(BTS A, BTS B);
    Dist(BTS A, BTS B, float d);
    BTS getBtsA();
    BTS getBtsB();
    float getDistance();
    float getHeight();
    void setDistance(float dist);
    void setBtsA(BTS bts);
    void setBtsB(BTS bts);
    void setHeight(float h);
    float computeDist(BTS A, BTS B);
    float computeHeight(Dist dist);

private:
    BTS A;
    BTS B;
    float distance;
    float height;
};

class Computation{
public:
    Computation();
    void setAntVect(vector<Ant> antVect);
    void setBtsVect(vector<BTS> btsVect);
    vector<BTS> getBtsVect();
    vector<Ant> getAntVect();
    float getCoordX();
    float getCoordY();
    void compute();
private:
    vector<BTS> btsVect;
    vector<Ant> antVect;
    float X;
    float Y;
    vector<Dist> computeAllDist(vector<BTS> btsVect);
};
#endif