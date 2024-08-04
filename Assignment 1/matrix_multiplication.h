#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <vector>
#include <tuple>

typedef std::vector<std::vector<int>> Matrix;

Matrix squareMatrixMultiply(const Matrix &A, const Matrix &B);
Matrix add(const Matrix &A, const Matrix &B);
Matrix subtract(const Matrix &A, const Matrix &B);
Matrix squareMatrixMultiplyRecursive(const Matrix &A, const Matrix &B);
Matrix strassen(const Matrix &A, const Matrix &B);
Matrix generateRandomMatrix(int n);
Matrix padMatrix(const Matrix &A, int newSize);
Matrix unpadMatrix(const Matrix &A, int originalSize);
std::tuple<double, double, double> measureTime(int n);

#endif // MATRIX_MULTIPLICATION_H
