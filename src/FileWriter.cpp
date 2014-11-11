#include "Headers.hpp"

using std::string;

const string MAPS_LINT_1 = "www.google.com/maps/place/";
const string MAPS_LINK_2 = "maps.google.com/maps?q="; 

FileWriter::FileWriter(string name){
	fileName = name;
	os.open(name.c_str());
	if(!os.is_open()){
        std::cerr << "neotevreno " << fileName << std::endl;
    }

}

void FileWriter::writeLine(string line){
	
    std::cout << line << std::endl;
    os << line;
    os.close();
}

void FileWriter::writeLine(string line, bool endl){
	os << line;
	if( endl) {
		os << std::endl;
	}
}

string FileWriter::parseGPS(float gps){
	char buf[32];
	sprintf(buf,"%.4f", gps);
	return buf;
}

string FileWriter::prepareGPSLink(float gpsWidth, float gpsHeight){
	string out = parseGPS(gpsWidth);
	out += ",";
	out += parseGPS(gpsHeight);
	return MAPS_LINK_2 + out;	
}


void FileWriter::closeFile(){
    fileName = "";
    os.close();
}