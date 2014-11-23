#include "Headers.hpp"

Dist::Dist(){}
Dist::Dist(BTS A, BTS B){
	this->A = A;
	this->B = B;
	this->distance = computeDist(B, A);
//	this->computeHeight(*this);
}

Dist::Dist(BTS A, BTS B, float d){
	this->A = A;
	this->B = B;
	this->distance = d;
	//this->height = computeHeight(*this);
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

void Dist::setM(float m){
	this->m = m;
}

float Dist::getM(){
	return this->m;
}



float Dist::computeC(){
	return 0.0;
}

float Dist::computeDist(BTS A, BTS B){
	return sqrt(pow(A.getDistance(), 2.0) + pow(B.getDistance(),2.0));
}


// m = (Ar^2 - Br^2) / 2d + d / 2
float Dist::computeMid(float Ar, float Br){
	
	return (pow(Ar, 2.0) - pow(Br, 2.0)) / (2.0 * distance) + distance / 2.0;
}

// v = sqrt(Ar^2 - m^2)    		
float Dist::computeHeight(Dist dist){
	float Ar = dist.getBtsA().getDistance();
	float m = dist.computeMid(Ar, dist.getBtsB().getDistance());	
	return sqrt(pow(Ar, 2.0) - pow(m, 2.0));
}