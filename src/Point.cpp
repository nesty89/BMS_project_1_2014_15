#include "Headers.hpp"

Point::Point(){

}

Point::Point(float x, float y){
	this->x = x;
	this->y = y;
}

float Point::getX(){
	return this->x;
}

float Point::getY(){
	return this->y;
}

void Point::setX(float x){
	this->x = x;
}

void Point::setY(float y){
	this->y = y;
}

bool Point::compare(Point A, Point B){
	return A.getX() == B.getX() && A.getY() == B.getY();  
}

PointPair::PointPair(Point A, Point B){
	this->A = A;
	this->B = B;
	this->d = distance(A,B);
}

PointPair::PointPair(Point A, Point B, int id){
	this->A = A;
	this->B = B;
	this->d = distance(A,B);
	this->id = id;
}

float PointPair::distance(Point A, Point B){
	return sqrt(pow(A.getX() - B.getX(), 2.0) + pow(A.getY() - B.getY(), 2.0));
}

Point PointPair::getPointA(){
	return this->A;
}

Point PointPair::getPointB(){
	return this->B;
}

float PointPair::getDistance(){
	return this->d;
}