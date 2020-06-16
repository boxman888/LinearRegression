#ifndef HOUSINGDATA_H
#define HOUSINGDDATA_H

#define COL_SIZE 13 // The # of dims will be const over train and test data.
class HousingData{
public:
    // Not putting below elements into an array for readability.
    // Could always condence to an array of strings and loop over the data.
    std::string crim;     // Per capita crime rate.
    std::string zn;       // Proportion of residential land zoned for lots over 25,000 sq.ft.
    std::string indus;    // Proportion of non-retail business acres per town.
    std::string chas;     // Charles River dummy variable (= 1 if tract bounds river; 0 otherwise)
    std::string nox;      // Nitric oxides concentration (parts per 10 million).
    std::string rm;       // Average number of rooms per dwelling.
    std::string age;      // Proportion of owner-occupied units built prior to 1940.
    std::string dis;      // Weighted distances to five Boston employment centres.
    std::string rad;      // Index of accessibility to radial highways.
    std::string tax;      // Full-value property-tax rate per $10,000.
    std::string ptratio;  // Pupil-teacher ratio by town.
    std::string B;        // 1000(Bk - 0.63)^2 where Bk is the proportion of blacks by town.
    std::string lstat;    // % lower status of the population.
    std::string medv;     // Median value of owner-occupied homes in $1000's.

    //friend std::istream& operator>>(std::istream& str, HousingData& data);
    void fill(HousingData& temp);
};

std::istream& operator>>(std::istream& str, HousingData& data);
#endif
