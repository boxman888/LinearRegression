# LinearRegression
Linear regression model performed on Boston housing data. Specificly focusing on housing values. The data here was taken from StatLib library and was composed by Harrison, D. and Rubinfeld, D.L. in 'Hedonic prices and the demand for clean air', J. Environ. Economics & Management, vol.5, 81-102, 1978. The dimension predicted in this code is the median value of owner-occupied homes in $1000's

## Setting Up
There is one external library needed before executing this source code. The Eigen library located at [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

Download the latest Eigen library and unpack it in the cloned repository. Add the path of the Eigen library to the Makefile

### Example
```
CXXFLAGS = -std=c++11 -Wall -fpic -O2 -I ./eigen/
```

## Running
Once the path to eigen has been connected to the make file. Simply run the make command.
```
foo@m1$ make
```