#include "Headers.hpp"
Dist::Dist(){}
Dist::Dist(BTS A, BTS B){
	this->A = A;
	this->B = B;
	this->distance = computeMidDist(A, B);
	this->computeHeight(*this);
}

Dist::Dist(BTS A, BTS B, float d){
	this->A = A;
	this->B = B;
	this->distance = d;
	this->height = computeHeight(*this);
}

BTS Dist::getBtsA(){
	return A;
}

BTS Dist::getBtsB(){
	return B;
}

float Dist::getDistance(){
	return distance;
}

float Dist::getHeight(){
	return height;
}

void Dist::setDistance(float dist){
	this->distance = dist;
}

void Dist::setBtsA(BTS bts){
	this->A = bts;
}

void Dist::setBtsB(BTS bts){
	this->B = bts;
}

void Dist::setHeight(float h){
	this->height = h;
}

float Dist::computeDist(BTS A, BTS B){
	return sqrt(pow((A.getLatitude() - B.getLatitude()), 2.0) + pow((A.getLongtitude() - B.getLongtitude()), 2.0));
}


// vypocitava to pro rovnostrany 

// m = (Ar^2 - Br^2) / 2d + d / 2
// v = sqrt(Ar^2 - m^2)    		
float Dist::computeHeight(Dist dist){
	float d = dist.getDistance();
	cout << "D:  " << d << endl;
	float Ar = dist.getBtsA().getDistance();
	cout << "Ar: " << Ar << endl;
	cout << "Br: " << dist.getBtsB().getDistance() << endl;
	float m = (pow(Ar, 2.0) - pow(dist.getBtsB().getDistance(), 2.0)) / (2.0 * d) + d / 2.0;
	cout << "M:  " << m << endl;
	cout << "V:  " << sqrt(pow(Ar, 2.0) - pow(m, 2.0)) << endl;
	
	return sqrt(pow(Ar, 2.0) - pow(m, 2.0));
}