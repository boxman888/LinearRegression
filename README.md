# LinearRegression
Linear regression model performed on Boston housing data. Specificly focusing on housing values. The data here was taken from StatLib library and was composed by Harrison, D. and Rubinfeld, D.L. in 'Hedonic prices and the demand for clean air', J. Environ. Economics & Management, vol.5, 81-102, 1978. The dimension predicted in this code is the median value of owner-occupied homes in $1000's

The purpose of this project is to explore the use of linear regression. Here batch gradient descent is used to minimize the cost of the Sum of Squared Errors (SSE).
## Objective
Here I only find the gradient with respect to `w`. The SSE is used as the optimization function.
```
E(w) = sum_i = 1 ... n (y_i-wx_i)^2 = (y-Xw)^T(y-Xw)
```
The derivative of the objective with respect to the variable `w` is 
```
w = (X^T*X)^-1X^T*y
```
![](https://blog.paperspace.com/content/images/2018/05/68747470733a2f2f707669676965722e6769746875622e696f2f6d656469612f696d672f70617274312f6772616469656e745f64657363656e742e676966.gif)

## Normalization
The data is normalized before being processed. 
The normalization function is:
```
    z_i = (x_i - min) / (max - min)
```
Without normalizing the data, the SSE will only increase. To make predictions with the learned weight/hypothesis coefficient vector, one must normalize the data they are analyzing first. Then solve for Y_bar.  Once Y_bar is found you can unnormalize Y_bar to get the desired value.

![](https://miro.medium.com/max/2972/1*vXpodxSx-nslMSpOELhovg.png)

## Setting Up
There is one external library needed before executing this source code. The Eigen library located at [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

Download the latest Eigen library and unpack it in the cloned repository. Add the path of the Eigen library to the Makefile.

## For Visual Studio Users
You can add the path of eigen to Configuration Properties -> VC++ Directories -> Include Directories

### Example path setup for Linux/Mac users
```
CXXFLAGS = -std=c++11 -Wall -fpic -O2 -I ./eigen/
```

## Running for Linux/Mac users
Once the path to eigen has been connected to the make file. Simply run the make command.
```
foo@m1$ make
```

## Math used
See this document for a more indepth view of the Matrix math use here [Simple Linear Regression in Matrix Format](https://www.stat.cmu.edu/~cshalizi/mreg/15/lectures/13/lecture-13.pdf)
