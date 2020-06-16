#include <iostream>
#include <fstream>
#include <Eigen/Dense> // Linear Algebra library. Don't forget to add path to Makefile.

#include "HousingData.h" // For reading data files.

void loadData(Eigen::MatrixXf &X, Eigen::VectorXf &Y, std::ifstream &fp){
    int r = 0;
    HousingData data;
    // Read data line by line and sotre it into X matrix.
    while (fp >> data){
        // Again this could be put into an array.
        // See HousingData.h for why it is currently structered this way.
        X(r,0) = 1; // Bias value.
        X(r,1) = std::stof(data.zn, NULL);
        X(r,2) = std::stof(data.zn, NULL);
        X(r,3) = std::stof(data.indus, NULL);
        X(r,4) = std::stof(data.chas, NULL);
        X(r,5) = std::stof(data.nox, NULL);
        X(r,6) = std::stof(data.rm, NULL);
        X(r,7) = std::stof(data.age, NULL);
        X(r,8) = std::stof(data.dis, NULL);
        X(r,9) = std::stof(data.rad, NULL);
        X(r,10) = std::stof(data.tax, NULL);
        X(r,11) = std::stof(data.ptratio, NULL);
        X(r,12) = std::stof(data.B, NULL);
        X(r,13) = std::stof(data.lstat, NULL);

        Y(r) = std::stof(data.medv, NULL); // Values of interest.
        r++;
    }

    fp.clear();
    fp.seekg(0, fp.beg); 
}
/**
 * @param fp is a file pointer.
 * Function gets the number of rows in a file.
 */
int getFileRowCount(std::ifstream &fp){
    int num_of_rows = 0;
    std::string rows;
    while (std::getline( fp, rows ))
        num_of_rows++;
    
    fp.clear();
    fp.seekg(0, fp.beg); 
    return num_of_rows;
}
/**
 * @param X Matrix of Quantitative Variables.
 * @param Y Vector of Response Variables.
 * Calculates a vector of weight coefficients based off traning data.
 * Useing a gradient descent method.
*/
Eigen::VectorXf calcOptimalWieghts(Eigen::MatrixXf &X, Eigen::VectorXf &Y){
    Eigen::MatrixXf Xt(X.cols(), X.rows());
    Eigen::VectorXf W( Y.size() );

    Xt = X.transpose();

    Eigen::HouseholderQR<Eigen::MatrixXf> qr(Xt*X);
    W = qr.solve(Xt) * Y;
    //W = ((Xt*X).inverse() * Xt) * Y;
    return W;
}
/**
 * @param X Matrix of Quantitative Variables.
 * @param W Learned vector of weight coefficients
 * @param Y Vector of Response Variables.
 * Measures the Sum Squared Error of the learned weights.
 */
float leastSquares(Eigen::MatrixXf &X, Eigen::VectorXf &W, Eigen::VectorXf &Y){
    Eigen::VectorXf e( Y.size() );
    e = (Y - X*W);
    for (int i = 0; i < e.size(); i++)
        e[i] = e[i]*e[i]/Y.size();

    return (float)e.sum();
}

int main()
{
    std::ifstream fp_train("./data/housing_train.csv");
    std::ifstream fp_test("./data/housing_test.csv");

    Eigen::MatrixXf X(getFileRowCount(fp_train), COL_SIZE+1);
    Eigen::MatrixXf X_test(getFileRowCount(fp_test), COL_SIZE+1);
    
    Eigen::VectorXf Y( X.rows() );
    Eigen::VectorXf Y_test( X_test.rows() );
    Eigen::VectorXf W;

    loadData(X, Y, fp_train);
    loadData(X_test, Y_test, fp_test);
    fp_train.close(); // Don't need this anymore, data is now in the matrix.
    fp_test.close();

    W = calcOptimalWieghts(X, Y);
    std::cout << "SSE for training set: " << leastSquares(X, W, Y) << std::endl;

    std::cout << "SSE for testing set: " << leastSquares(X_test, W, Y_test) << std::endl;

    return 0;
}