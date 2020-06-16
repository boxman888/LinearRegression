# LinearRegression
Linear regression model performed on Boston housing data. Specificly focusing on housing values. The data here was taken from StatLib library and was composed by Harrison, D. and Rubinfeld, D.L. in 'Hedonic prices and the demand for clean air', J. Environ. Economics & Management, vol.5, 81-102, 1978. The dimension predicted in this code is the median value of owner-occupied homes in $1000's

The purpose of this project is to explore the use of linear regression. Here a gradient approach is used.
## Objective
Here I only find the gradient with respect to E(w)
<!—e(w) = \sum_{i=1}^{n}(yi-wxi)^2 = (y-Xw)^T(y-Xw)

The derivative of the objective wit hrespect to the variable `w` is 

<!- w = (X^TX)^-1X^Ty -->

![](https://donsoft.io/deep-learning-with-rnns/images/gradient_descent_cropped.gif)

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

## Math used
See this document for a more indepth view of the Matrix math use here [Simple Linear Regression in Matrix Format](https://www.stat.cmu.edu/~cshalizi/mreg/15/lectures/13/lecture-13.pdf)