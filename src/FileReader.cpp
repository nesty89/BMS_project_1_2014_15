#include "Headers.hpp"
using std::getline;
using std::string;

FileReader::FileReader(string name){
    fileName = name;
    end = false;
    is.open(name.c_str(), std::ifstream::in);
    if(!is.is_open()){
        std::cerr << "neotevreno " << fileName<< std::endl;
    }
}

string FileReader::GetLine() {
    string str;
    if(!end && !is.good() || !getline(is, str) ){
        end = true;
        return "";
    }
    return str;
}

bool FileReader::isEnd() {
    return end;
}


void FileReader::initNew(string name){
    closeFile();
    fileName = name;
    is.open(name.c_str(), std::ifstream::in);
    if(!is.is_open()){
        std::cerr << "neotevreno" << std::endl;
    }
}

void FileReader::closeFile(){
    fileName = "";
    end = false;
    is.close();
}