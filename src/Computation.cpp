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
	vector<PointPair> pairs;
	int position;
	vector<Point> points;
	bool fa = false, fb = false;
	float min = INFINITY;
	float max = 0;
	for(int i = 0; i < vp.size(); i++){
		for(int j = i; j < vp.size(); j++){
			if ( i != j){
				PointPair pp (vp[i], vp[j]);
				pairs.push_back(pp);
			}

		}
	}
	vector<vector<Point> > clusters;
	for (int i = 0; i < vp.size(); i++){
		vector<Point> v;
		v.push_back(vp[i]);
		clusters.push_back(v);
	}
	bool end = false;
	int cid;
	int Ap,Bp;
	while(!end){
		min = INFINITY;

		for ( int i = 0; i < pairs.size(); i++){
			if(pairs[i].getDistance() <= min ){
				min = pairs[i].getDistance();
				position = i;
			}
		}	

		for(int i = 0; i < clusters.size(); i++){
			for(int j = 0; j < clusters[i].size(); j++){
				if(pairs[position].getPointA().compare(pairs[position].getPointA(), clusters[i][j])){
					Ap = i;
				}
				if(pairs[position].getPointB().compare(pairs[position].getPointB(), clusters[i][j])){
					Bp = i;
				}
			}
		}
		if(Ap != Bp){
			for(int i = 0; i < clusters[Bp].size(); i++){
				clusters[Ap].push_back(clusters[Bp][i]);
			}
			clusters.erase(clusters.begin() + Bp);
		} 
		pairs.erase(pairs.begin() + position);

		for(int i = 0; i < clusters.size(); i++){
			if(clusters[i].size() >= vp.size()/2){
				cid = i;
				end = true;
			}
		}
	}

	float sumX = 0.0, sumY = 0.0;
	for ( int i = 0; i <  clusters[cid].size(); i++){
		sumX += clusters[cid][i].getX();
		sumY += clusters[cid][i].getY();
	}
	
	sumX = sumX / (float) clusters[cid].size();
	sumY = sumY / (float) clusters[cid].size();
	
	sumX = 0.0;
	sumY = 0.0;
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