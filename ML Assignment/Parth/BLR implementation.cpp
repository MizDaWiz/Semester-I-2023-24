#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Function to read data from CSV file
MatrixXd readCSV(const string& filename, int rows, int cols) {
    MatrixXd data(rows, cols);
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> data(i, j);
            }
        }
        file.close();
    }
    return data;
}

// Function to implement Bayesian Linear Regression
void bayesianLinearRegression(const MatrixXd& X, const VectorXd& y, double alpha, double beta) {
    int N = X.rows(); // Number of data points
    int M = X.cols(); // Number of features

    // Prior
    MatrixXd S0 = alpha * MatrixXd::Identity(M, M);
    VectorXd m0 = VectorXd::Zero(M);

    // Compute posterior
    MatrixXd SN = S0 + beta * X.transpose() * X;
    VectorXd mN = SN.inverse() * (S0 * m0 + beta * X.transpose() * y);

    // Print posterior parameters
    cout << "Posterior Mean (mN):" << endl << mN << endl;
    cout << "Posterior Covariance (SN):" << endl << SN << endl;
}

int main() {
    // Read data from CSV file
    MatrixXd data = readCSV("your_dataset.csv", num_rows, num_cols);

    // Extract features (X) and target variable (y)
    MatrixXd X = data.leftCols(num_cols - 1);
    VectorXd y = data.col(num_cols - 1);

    // Hyperparameters
    double alpha = 1.0; // Prior precision
    double beta = 1.0;  // Noise precision

    // Perform Bayesian Linear Regression
    bayesianLinearRegression(X, y, alpha, beta);

    return 0;
}