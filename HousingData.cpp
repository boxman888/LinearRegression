#include <string>
#include <sstream>
#include <istream>
#include "HousingData.h"

std::istream& operator>>(std::istream& str, HousingData& data){
    std::string line;
    HousingData temp;
    if (std::getline( str, line )){
        std::stringstream iss(line);
        // Test for bad rows.
        if (std::getline(iss, temp.crim, ',')      &&
            std::getline(iss, temp.zn, ',')        &&
            std::getline(iss, temp.indus, ',')     &&
            std::getline(iss, temp.chas, ',')      &&
            std::getline(iss, temp.nox, ',')       &&
            std::getline(iss, temp.rm, ',')        &&
            std::getline(iss, temp.age, ',')       &&
            std::getline(iss, temp.dis, ',')       &&
            std::getline(iss, temp.rad, ',')       &&
            std::getline(iss, temp.tax, ',')       &&
            std::getline(iss, temp.ptratio, ',')   &&
            std::getline(iss, temp.B, ',')         &&
            std::getline(iss, temp.lstat, ',')     &&
            std::getline(iss, temp.medv, ',')){
                data.fill(temp);
            }

        else
            str.setstate(std::ios::failbit); // If bad row set stream failbit.
    }
    return str;
}
// Fill data of current object with that held in the temp object.
void HousingData::fill(HousingData& other){
    std::swap(crim, other.crim);
    std::swap(zn, other.zn);
    std::swap(indus, other.indus);
    std::swap(chas, other.chas);
    std::swap(nox, other.nox);
    std::swap(rm, other.rm);
    std::swap(age, other.age);
    std::swap(dis, other.dis);
    std::swap(rad, other.rad);
    std::swap(tax, other.tax);
    std::swap(ptratio, other.ptratio);
    std::swap(B, other.B);
    std::swap(lstat, other.lstat);
    std::swap(medv, other.medv);
}