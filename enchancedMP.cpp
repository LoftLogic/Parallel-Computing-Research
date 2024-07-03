#include <omp.h>
#include <vector>
#include <iostream>

using namespace std;

void multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, vector<vector<int>>& matrixC) {
    int numRowsA = matrixA.size();
    int numColsA = matrixA[0].size();
    int numRowsB = matrixB.size();
    int numColsB = matrixB[0].size();
    if (numColsA != numRowsB) {
        cout << "Dimensions don't match, cannot multiply" << endl;
        return;
    }

    cout << "Dimensions match, multiplying matrices" << endl;

    #pragma omp parallel for
    
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsB; j++) {
            int sum = 0;
            for (int k = 0; k < numColsA; k++) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            matrixC[i][j] = sum;
        }
    }
}

int main() {
    vector<vector<int>> matrixA = {{1, 2, 8}, {5, 6, 11}, {9, 10, 17}};
    vector<vector<int>> matrixB = {{4, 5, 6}, {8, 9, 10}, {20, 2, 17}};
    vector<vector<int>> matrixC(matrixA.size(), vector<int>(matrixB[0].size(), 0));

    multiplyMatrices(matrixA, matrixB, matrixC);

    cout << "Working" << endl;
    cout << "Product: " << endl;
    for (int i = 0; i < matrixC.size(); i++) {
        for (int j = 0; j < matrixC[i].size(); j++) {
            cout << matrixC[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
