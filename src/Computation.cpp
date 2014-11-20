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




vector<Dist> Computation::computeAllDist(vector<BTS> btsVect){
	vector<Dist> distVect;
	for(int i = 0; i < btsVect.size(); i++){
		for(int j = i; j < btsVect.size(); j++){
			if(btsVect[i].getCID() != btsVect[j].getCID()){
				Dist d(btsVect[i], btsVect[j]);
				if (d.getDistance() > 0.0){ // mozna lepsi podminku *1000   > 0.000001 nebo tak neco
					d.setHeight(d.computeHeight(d));
					cout << d.getHeight() << endl;
					distVect.push_back(d); 
				}
			}
		}
	}
	return distVect;
}

void Computation::compute(){
	vector<Dist> distVect;
	distVect = computeAllDist(btsVect); 

	
	//for (int i = 0; i < distVect.size(); i++ ){
	//	cout << distVect[i].getDistance() << endl;
	//}

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