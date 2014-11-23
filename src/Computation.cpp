#include "Headers.hpp"
#include "UTM.h"

Computation::Computation(){

};


void Computation::setAntVect(vector<Ant> antVect){
	this->antVect = antVect;
}

void Computation::setBtsVect(vector<BTS> btsVect){
	this->btsVect = btsVect;
}

vector<BTS> Computation::getBtsVect(){
	return btsVect;
}

vector<Ant> Computation::getAntVect(){
	return antVect;
}


vector<Dist> Computation::computeAllDist(vector<BTS> btsVect){
	vector<Dist> distVect;
	for(int i = 0; i < btsVect.size(); i++){
		for(int j = i; j < btsVect.size(); j++){
			if(btsVect[i].getCID() != btsVect[j].getCID()){
				Dist d(btsVect[i], btsVect[j]);
				if (d.getDistance() > 0.0){ // mozna lepsi podminku *1000   > 0.000001 nebo tak neco
					d.setHeight(d.computeHeight(d));
					distVect.push_back(d); 
				}
			}
		}
	}
	return distVect;
}

// Sx = Ax + (m / d) * (Bx - Ax)
// Sy = Ay + (m / d) * (By - Ay)
// Cx1,2 = Sx +- (v / d) (Ay - By)
// Cy1,2 = Sy +- (v / d) (Ax - Bx)

vector<Point> computeAllMobileLocations(vector<Dist> distVect){
	float Sx, Sy, Cx1, Cx2, Cy1, Cy2;
	vector<Point> vp;
	for(int i = 0; i < distVect.size(); i++){
		distVect[i].setM(distVect[i].computeMid(distVect[i].getBtsA().getDistance(),distVect[i].getBtsB().getDistance() ));
		Sx = distVect[i].getBtsA().getLatitude() + (distVect[i].getM()/ distVect[i].getDistance()) * (distVect[i].getBtsB().getLatitude() - distVect[i].getBtsA().getLatitude());
		Sy = distVect[i].getBtsA().getLongtitude() + (distVect[i].getM()/ distVect[i].getDistance()) * (distVect[i].getBtsB().getLongtitude() - distVect[i].getBtsA().getLongtitude());
		Cx1 = Sx + (distVect[i].getHeight() / distVect[i].getDistance()) * (distVect[i].getBtsA().getLongtitude() -  distVect[i].getBtsB().getLongtitude());
		Cy1 = Sy + (distVect[i].getHeight() / distVect[i].getDistance()) * (distVect[i].getBtsA().getLatitude() -  distVect[i].getBtsB().getLatitude());
		Cx2 = Sx - (distVect[i].getHeight() / distVect[i].getDistance()) * (distVect[i].getBtsA().getLongtitude() -  distVect[i].getBtsB().getLongtitude());
		Cy2 = Sy - (distVect[i].getHeight() / distVect[i].getDistance()) * (distVect[i].getBtsA().getLatitude() -  distVect[i].getBtsB().getLatitude());
		vp.push_back(Point(Cx1,Cy1));
		vp.push_back(Point(Cx2,Cy2));
	}
	return vp;
}

Point Computation::findMobileLoc(std::vector<Point> vp){
	
	float sumX = 0.0, sumY = 0.0;
	for (int i = 0; i < vp.size(); i++){
		sumX += vp[i].getX();
		sumY += vp[i].getY();  
	}

	sumX = sumX / (float) vp.size();
	sumY = sumY / (float) vp.size();
	
	Point p(sumX, sumY);
	return p;
}

//  C
//  | \
//  |  \
//  |   \
//  S -- A

// v = |CS|  ...... vyska vyska v
// S .............. bod kolmice na AB
// m = |AS| ....... cast usecky AB
// C .............. hledany bod
// Ar, Br ......... spocitane distance

// m = (Ar^2 - Br^2) / 2d + d / 2
// v = sqrt(Ar^2 - m^2)
// Sx = Ax + (m / d) * (Bx - Ax)
// Sy = Ay + (m / d) * (By - Ay)
// Cx1,2 = Sx +- (v / d) (Ay - By)
// Cy1,2 = Sy +- (v / d) (Ax - Bx)

Point Computation::compute(){
 	vector<Dist> distVect;
 	distVect = computeAllDist(btsVect);
 	vector<Point> vp;
 	vp = computeAllMobileLocations(distVect);
 	return findMobileLoc(vp);

}