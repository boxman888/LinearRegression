/********************************************************************
 * Implements multivariate regression analysis in an attempt to learn
 * the weight/hypothesis coefficients for a system of eqations.
 * Created: Jun 17 2020
 * Author: Ethan Patterson
 *******************************************************************/

#include <iostream>
#include <fstream>
#include <Eigen/Dense> // Linear Algebra library. Don't forget to add path to Makefile.

#include "HousingData.h" // For reading data files.

#ifndef ITR
#define ITR 2000
#endif

#ifndef ALPHA
#define ALPHA 0.01
#endif

// Made for convinance of managing
// the max and min values of the data.
struct Tuple{
    float x;
    float y;
};

void loadData(Eigen::MatrixXf &X, Eigen::VectorXf &Y, std::ifstream &fp){
    int r = 0;
    HousingData data;
    // Read data line by line and sotre it into X matrix.
    while (fp >> data){
        // Again this could be put into an array.
        // See HousingData.h for why it is currently structered this way.
        //X(r,0) = 1; // Dummy value.
        X(r,0) = std::stof(data.crim, NULL);
        X(r,1) = std::stof(data.zn, NULL);
        X(r,2) = std::stof(data.indus, NULL);
        X(r,3) = std::stof(data.chas, NULL);
        X(r,4) = std::stof(data.nox, NULL);
        X(r,5) = std::stof(data.rm, NULL);
        X(r,6) = std::stof(data.age, NULL);
        X(r,7) = std::stof(data.dis, NULL);
        X(r,8) = std::stof(data.rad, NULL);
        X(r,9) = std::stof(data.tax, NULL);
        X(r,10) = std::stof(data.ptratio, NULL);
        X(r,11) = std::stof(data.B, NULL);
        X(r,12) = std::stof(data.lstat, NULL);

        Y(r) = std::stof(data.medv, NULL); // Values of interest.
        r++;
    }

    fp.clear();
    fp.seekg(0, fp.beg);// Reset to head of file.
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
    fp.seekg(0, fp.beg); // Reset to head of file.
    return num_of_rows;
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
/**
 * @param X Matrix of Quantitative Variables.
 * @param W Learned vector of weight coefficients, hypothosis.
 * @param Y Vector of Response Variables.
 * @param alpha The learning rate to apply.
 * @param iter The number of iterations to complete.
 * Use batch gradient descent to minimize the cost/error of the system.
 * Returns the cost history of the system over iterations.
 */
float* BGD(Eigen::MatrixXf &X, Eigen::VectorXf &W, Eigen::VectorXf &Y, float alpha, int itr, const Tuple &maxmin){
    Eigen::VectorXf Hypo ( Y.size() );
    Eigen::VectorXf Loss ( Y.size() );
    Eigen::VectorXf Gradient ( Y.size() );
    float* costHistory = new float[itr];

    float cost = 0.0;
    for (int i = 0; i < itr; i++){
        Hypo = X*W;
        Loss = Hypo - Y;
        Gradient = (X.transpose() * Loss) / Y.size();
        W = W - alpha * Gradient;
        cost = leastSquares(X, W, Y);
        costHistory[i] = cost*(maxmin.x - maxmin.y) + maxmin.y;
    }
    return costHistory;
}
/**
 * @param X Matrix of Quantitative Variables.
 * @param Y Vector of Response Variables.
 * Nomralize the data between 0 and 1.
 * Returns a tuple of the max and min value.
 * Max is the x component and min is the y.
 */
Tuple normalize(Eigen::MatrixXf &X, Eigen::VectorXf &Y){
    float max_x, max_y, max;
    float min_x, min_y, min;
    Tuple maxmin;

    Eigen::MatrixXf::Index maxRow,maxCol;
    Eigen::MatrixXf::Index minRow,minCol;

    max_x = X.maxCoeff(&maxRow, &maxCol);
    max_y = Y.maxCoeff(&maxRow, &maxCol);

    min_x = X.minCoeff(&minRow, &minCol);
    min_y = Y.minCoeff(&minRow, &minCol);

    if (max_x < max_y)
        max = max_y;
    else
        max = max_x;

    if (min_x < min_y)
        min = min_x;
    else
        min = min_y;

    for (int i = 0; i < X.rows(); i++){
        for (int j = 0; j < X.cols(); j++){
            X(i,j) = (X(i,j) - min) / (max - min);
        }
    }

    for (int i = 0; i < Y.rows(); i++)
        Y(i) = (Y(i) - min) / (max - min);

    maxmin.x = max;
    maxmin.y = min;

    return maxmin;
}
/**
 * @param cost Dynamic array of cost history.
 * @param W Learned vector of weight coefficients, hypothesis.
 * @param Y Vector of Response Variables.
 * Saves data produced such as the cost history, weights/hypotheses, and normalization min max.
 */
void saveData(float *cost, const Tuple &maxmin, Eigen::VectorXf &W){
    std::ofstream weights("weights.csv");
    std::ofstream norm("normalize.csv");
    std::ofstream costHistory("cost_history.csv");

    if (weights.is_open()){
        for (int i = 0; i < W.size()-2; i++)
            weights << W(i) << ",";
        weights << W(W.size()-1);
    }
    weights.close();

    if (norm.is_open()){
        norm << "max" << "," << maxmin.x << "\n";
        norm << "min" << "," << maxmin.y << "\n";
    }
    norm.close();

    if(costHistory.is_open()){
        for (int i = 0; i < ITR; i++)
            if ( i % 2 ) // No need to see cost at every step.
                costHistory << i << "," << cost[i] << "\n";
    }
    costHistory.close();
}

int main()
{
    // Files in training and testing data.
    std::ifstream fp_train("./data/data/housing_train.csv");
    std::ifstream fp_test("./data/data/housing_test.csv");

    // Build maxtix for traning and testing data.
    Eigen::MatrixXf X(getFileRowCount(fp_train), COL_SIZE);
    Eigen::MatrixXf X_test(getFileRowCount(fp_test), COL_SIZE);

    // Build Vectors for target variables and weight/hypotheses.
    Eigen::VectorXf Y( X.rows() );
    Eigen::VectorXf Y_test( X_test.rows() );
    Eigen::VectorXf W ( X.cols() );// Size is the number of features/dimensions.

    Tuple maxmin; // Used to keep track of max and min value during normalization.
    float *costHistory; // Pointer for array to cost history.

    // Load data into matrices and vectors.
    loadData(X, Y, fp_train);
    loadData(X_test, Y_test, fp_test);
    fp_train.close(); // Don't need this anymore, data is now in the matrix.
    fp_test.close();

    // Set all initial weight/hypothesis values to 0.
    W = Eigen::VectorXf::Ones( X.cols() ) * 0;

    normalize(X, Y); // Normalize data.
    maxmin = normalize(X_test, Y_test); // Keep max and min values for future data sets.
    std::cout << "Max: " << maxmin.x << " Min: " << maxmin.y << std::endl;

    // Run batch gradient descent.
    costHistory = BGD(X, W, Y, ALPHA, ITR, maxmin);
    std::cout << "SSE for training set: " << leastSquares(X, W, Y) *
     (maxmin.x - maxmin.y) + maxmin.y << std::endl;
    std::cout << "SSE for testing set: " << leastSquares(X_test, W, Y_test) *
     (maxmin.x - maxmin.y) + maxmin.y << std::endl;

    saveData(costHistory, maxmin, W);
    delete costHistory;

    return 0;
}
