#include <iostream>
#include <vector>
#include <thread>
using namespace std;

//Evan Li
//Parallel Computing Research under Professor David Kaeli
//4-5

//Multiply Portion: Given certain rows and two matrices, perform matrix matrix multiplication and append the results
//to a resultant matrix

//2D Vector of Integers: Matrix A, Matrix B, Matrix C
//Matrix A and Matrix B are given as filled out 2D vectors and are multiplied together
//Matrix C is a resultant matrix
//Row Start and Row End are indices to designate the matix to certain indices
void multiplyPortion(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, vector<vector<int>>& matrixC,
        int rowStart, int rowEnd){
        //Iterate through rows
        for (int i=rowStart; i<rowEnd; i++){
            //Iterate through columns
                for (int j=0; j<matrixB[0].size(); j++){
                    //Dot product from Matrix A row and Matrix B column, throw in matrix C
                        for (int k=0; k<matrixB[0].size(); k++){
                                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                        }
                }
        }
}

//Sets up threads, and designates portions to undergoe matrix matrix multiplcation

//2D Vector of Integers: Matrix A, Matrix B, Matrix C
//Integer: numThreads
//Matrix A and Matrix B are given as filled out 2D vectors and are to be multiplied together
//numThreads is the number of threads
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, const vector<vector<int>>& matrixB, int numThreads){
        //Intialize matrices dimensions
        int numRowsA = matrixA.size();
        int numColsA = matrixA[0].size();
        int numRowsB = matrixB.size();
        int numColsB = matrixB[0].size();
        
        //Check if matrix matrix multiplication is possible (C1 == R2)
        if (numColsA != numRowsB) {
                throw invalid_argument("Dimensions do not match for multiplication.");
        } else {
                cout << "Dimensions match, preparing multiplication" << endl;
        }
         
        //Make Resultant Matrix, fill it with 0
        vector<vector<int>> matrixC(numRowsA, vector<int>(numColsB,0));

        //Make a vector filled with threads
        vector <thread> threads;
        
        //Find out how many rows each thread will cover
        int rowsPerThread = numRowsA / numThreads;
        //Find out how many extra rows there are
        int extraRows = numRowsA % numThreads;
        int start = 0;
        
        //Create threads, and assign them 
        for (int i=0; i<numThreads; i++){
                //If there are more extra threads than the current iteration, add a row
                int end = start + rowsPerThread + (extraRows > i ? 1 : 0);
                //Emplace_back(): Places at the back (duh)
                //ref(): Properly and safely handles the matrices by reference instead of making copies
                //threads() is a constructor, which takes in a callable object (e.g a function) and its parameters
                //Allows the program to run in parallel
                threads.emplace_back(multiplyPortion, ref(matrixA), ref(matrixB), ref(matrixC), start, end);
                start = end;
        }
        //Wait for threads to finish their task
        for (thread& t : threads){
                t.join();
        }
        //Return result matrix
        return matrixC;

}

int main(){
        //Make two 2d matrices filled with ints
        vector<vector<int>> matrixA = {{1, 2, 8}, {5,6, 11}, {9,10, 17}};
        vector<vector<int>> matrixB = {{4,5,6}, {8,9,10}, {20, 2, 17}};
        cout << "Matrix A" << endl;
        //Display A and B
        for (int i=0; i<matrixA.size();i++){
                for (int j=0; j<matrixA[i].size(); j++){
                        cout << matrixA[i][j] << " ";
                }
                cout << endl;
        }
        cout << "Matrix B" << endl;
        for (int i=0; i<matrixB.size();i++){
                for (int j=0; j<matrixB[i].size(); j++){
                        cout << matrixB[i][j] << " ";
                }
                cout << endl;
        }

        //Perform matrix matrix multiplcation with 3 threads
        vector<vector<int>> matrixC = multiplyMatrices(matrixA, matrixB, 3);
        //Print the resulting matrix
        cout << "Product Matrix" << endl;
        for (int i=0;i<matrixC.size();i++){
                for (int j=0;j<matrixC[i].size();j++){
                        cout << matrixC[i][j] << " ";
                        }
                        cout << endl;
                } 

        }

                    