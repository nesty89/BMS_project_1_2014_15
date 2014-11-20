#include "Headers.hpp"
#include <cmath>
using namespace std;
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

float Computation::getCoordX(){
	return X;
}

float Computation::getCoordY(){
	return Y;
}

float Computation::computeMidDist( BTS A, BTS B){
	return sqrt(pow((A.getLatitude() - B.getLatitude()),2.0) + pow((A.getLongtitude() - B.getLongtitude()), 2.0));
}

float Computation::computeMPartDist(BTS A, BTS B) {
	float dist = computeMidDist(A, B); 
	return dist;
}

void Computation::compute(){
	float midDist = 0.0;
	float mpart = 0.0;
    for(int i = 0; i < btsVect.size(); i++){
    	for(int j = i; j < btsVect.size(); j++){
    		if(btsVect[i].getCID() == btsVect[j].getCID()){
    			continue;
    		}
    	//	cout << btsVect[i].getCID() << " " << btsVect[j].getCID() << endl;
    	//	cout << computeMidDist(btsVect[i], btsVect[j]) << endl;
    		mpart = computeMPartDist(btsVect[i], btsVect[j]);// mozna presunout vypocet midDist do comupteMPartDist
    		
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
    	}
    }
}