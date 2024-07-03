#include <iostream>
#include <vector>
#include <thread>
using namespace std;

//Evan Li
//Parallel Computing Research under Professor David Kaeli
//4-5




void multiplyPortion(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, vector<vector<int>>& matrixC,
        int rowStart, int rowEnd){
        for (int i=rowStart; i<rowEnd; i++){
                for (int j=0; j<matrixB[0].size(); j++){
                        for (int k=0; k<matrixB[0].size(); k++){
                                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                        }
                }
        }
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, int numThreads){
        int numRowsA = matrixA.size();
        int numColsA = matrixA[0].size();
        int numRowsB = matrixB.size();
        int numColsB = matrixB[0].size();
        
        if (numColsA != numRowsB) {
                throw invalid_argument("Dimensions do not match for multiplication.");
        } else {
                cout << "Dimensions match, preparing multiplication" << endl;
        }
         
        vector<vector<int>> matrixC(numRowsA, vector<int>(numColsB,0));
        vector <thread> threads;
        
        int rowsPerThread = numRowsA / numThreads;
        int extraRows = numRowsA % numThreads;
        int start = 0;
        for (int i=0; i<numThreads; i++){
                int end = start + rowsPerThread + (extraRows > i ? 1 : 0);
                threads.emplace_back(multiplyPortion, ref(matrixA), ref(matrixB), ref(matrixC), start, end);
                start = end;
        }
        for (thread& t : threads){
                t.join();
        }
        return matrixC;

}

int main(){
        vector<vector<int>> matrixA = {{1, 2, 8}, {5,6, 11}, {9,10, 17}};
        vector<vector<int>> matrixB = {{4,5,6}, {8,9,10}, {20, 2, 17}};
        vector<vector<int>> matrixC = multiplyMatrices(matrixA, matrixB, 3);
        cout << "Working" << endl;
        for (int i=0;i<matrixC.size();i++){
                for (int j=0;j<matrixC[i].size();j++){
                        cout << matrixC[i][j] << " ";
                }
                cout << endl;
        } 

}