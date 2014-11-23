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
    void setULocation(string loc);
    string getULocation();
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
    string uLoc;
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
class Point{
public:
    Point();
    Point(float x, float y);
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);
    bool compare(Point A, Point B);
private:
    float x;
    float y;
};

class PointPair{
public:
    PointPair(Point A, Point B);
    PointPair(Point A, Point B, int id);
    float distance(Point A, Point B);
    Point getPointA();
    Point getPointB();
    float getDistance();
    int id;
private:
    Point A;
    Point B;
    float d;
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
    float getM();
    void setDistance(float dist);
    void setBtsA(BTS bts);
    void setBtsB(BTS bts);
    void setHeight(float h);
    void setM(float m);
    float computeC();
    float computeDist(BTS A, BTS B);
    float computeMid(float Ar, float Br);
    float computeHeight(Dist dist);
private:
    BTS A;
    BTS B;
    float distance;
    float height;
    float m;
};

class Computation{
public:
    Computation();
    void setAntVect(vector<Ant> antVect);
    void setBtsVect(vector<BTS> btsVect);
    vector<BTS> getBtsVect();
    vector<Ant> getAntVect();
    Point compute();
    Point findMobileLoc(std::vector<Point> vp);
private:
    vector<BTS> btsVect;
    vector<Ant> antVect;
    vector<Dist> computeAllDist(vector<BTS> btsVect);
};
#endif