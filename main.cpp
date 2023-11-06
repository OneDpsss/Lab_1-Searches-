#include "bits/stdc++.h"
using namespace std;

class Matrix {
private:
    int** matrix;
    int rows;
    int columns;
    int key;
    int binSearch(int row, int left, int right) {
        while (left <= right) {
            int middle = (left + right) / 2;
            if (matrix[row][middle] == key) {
                return middle;
            }
            if (matrix[row][middle] > key) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
        return left;
    }
public:
    Matrix(int InputRows, int InputColumns, int InputKey) {
        rows = InputRows;
        columns = InputColumns;
        key = InputKey;
        matrix = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[columns];
        }
    }
    void TheSecondGenerateMethod() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = (columns / rows * i + j) * 2;
            }
        }
    }
    void TheFirstGenerateMethod() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                matrix[i][j] = (columns / rows * (i + 1) * (j + 1)) * 2;
            }
        }
    }
    bool LadderSearch() {
        int row = 0, column = columns - 1;
        while (row < rows && column >= 0){
            if (matrix[row][column] == key) {
                return true;
            }else if (matrix[row][column] > key) {
                column--;
            }else{
                row++;
            }
        }
        return false;
    }
    bool LadderExpSearch() {
        int row = 0, column = columns - 1;
        while (row < rows){
            if (matrix[row][column] == key){
                return true;
            }else if (matrix[row][column] > key){
                int i = 1;
                while (column - i > - 1 and matrix[row][column - i] >= key){
                    i *= 2;
                }
                column = binSearch(row,max(column - i,0),column - i / 2);
                if (matrix[row][column] == key)
                    return true;
                else{
                    column--;
                }
            }else {
                row++;
            }
        }
        return false;
    }
    bool BinarySearch() {
        for (int i = 0; i < rows; ++i) {
            int result = binSearch(i, 0, columns - 1);
            if (matrix[i][result] == key) {
                return true;
            }
        }
        return false;
    }
};


void printTimes(long long sumBinaryTimes, long long sumLadderTimes, long long sumExpTimes,
                vector<long long> &binaryTimes, vector<long long> &ladderTimes, vector<long long> &expTimes,int numberOfTests) {
    cout << "Среднее время бинарного поиска: " << sumBinaryTimes / numberOfTests << "\n";
    cout << "Среднее время лестничного поиска: " << sumLadderTimes / numberOfTests << "\n";
    cout << "Среднее время экспоненциального поиска: " << sumExpTimes / numberOfTests << "\n";
    cout << "\n";
}

void RunningTests(int rows, int columns, int numberOfTests, string generationWay) {
    vector<long long> binaryTimes,ladderTimes,expTimes;
    Matrix Matrix(rows, columns, generationWay == "First" ? 2 * columns + 1 : 16 * columns + 1);
    if (generationWay == "First") {
        Matrix.TheFirstGenerateMethod();
    } else {
        Matrix.TheSecondGenerateMethod();
    }
    for (int i = 0; i < numberOfTests; ++i) {
        using namespace std::chrono;
        auto start = steady_clock::now();
        Matrix.BinarySearch();
        auto end = steady_clock::now();
        binaryTimes.push_back(duration_cast<nanoseconds>(end-start).count());
        start = steady_clock::now();
        Matrix.LadderSearch();
        end = steady_clock::now();
        ladderTimes.push_back(duration_cast<nanoseconds>(end-start).count());
        start = steady_clock::now();
        Matrix.LadderExpSearch();
        end = steady_clock::now();
        expTimes.push_back(duration_cast<nanoseconds>(end-start).count());
    }
    long long sumBinaryTimes = 0, sumLadderTimes = 0, sumExpTimes = 0;
    for (int i = 0; i < numberOfTests;i ++) {
        sumBinaryTimes += binaryTimes[i];
        sumLadderTimes += ladderTimes[i];
        sumExpTimes += expTimes[i];
    }
    cout << "Размер матрицы: " << rows << "x" << columns << ":" << endl;
    if (generationWay == "First") {
        cout << "Первый способ генерации:" << endl;
        printTimes(sumBinaryTimes, sumLadderTimes, sumExpTimes, binaryTimes, ladderTimes, expTimes,numberOfTests);
    } else {
        cout << "Второй способ генерации:" << endl;
        printTimes(sumBinaryTimes, sumLadderTimes, sumExpTimes, binaryTimes, ladderTimes, expTimes,numberOfTests);
    }
}

int main() {
    int rows = 2, columns = 8192, numberOfTests = 50000;
    while (rows <= 8912) {
        RunningTests(rows, columns, numberOfTests, "First");
        RunningTests(rows, columns, numberOfTests, "Second");
        rows = rows * 2;
    }
    return 0;
}
