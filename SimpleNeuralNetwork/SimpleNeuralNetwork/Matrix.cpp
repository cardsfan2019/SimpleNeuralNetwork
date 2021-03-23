#include "Matrix.h"
#include <corecrt_malloc.h>
#include <stdlib.h>

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->values = nullptr;
}

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->values = (float*) malloc(sizeof(float) * rows * cols);
}

Matrix Matrix::copy() {
    Matrix result(rows, cols);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            float val = this->get(i, j);
            result.set(i, j, val);
        }
    }

    return result;
}

Matrix Matrix::fromArray(float arr[], int length) {
    Matrix result(length, 1);
    for (int i = 0; i < result.rows; i++) {
        result.set(i, 0, arr[i]);
    }
    return result;
}

float* Matrix::toArray() {
    float* arr = (float*) malloc(sizeof(float) * this->rows * this->cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float* spot = arr + (i + j * cols);
            *spot = this->get(i, j);
        }
    }
    return arr;
}

void Matrix::multiply(float n) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float current = this->get(i, j);
            this->set(i, j, current * n);
        }
    }
}

void Matrix::add(float n) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float current = this->get(i, j);
            this->set(i, j, current + n);
        }
    }
}

Matrix Matrix::random(int rows, int cols) {
    Matrix result(rows, cols);
    result.randomize();
    return result;
}

void Matrix::randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int randInt = rand() % 200; //integer 0 - 199
            float randFloat = randInt / 200.0; //float 0.0 - 2.0
            this->set(i, j, randFloat - 1.0);
        }
    }
}

Matrix Matrix::subtract(Matrix a, Matrix b) {
    Matrix result(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            float sub = a.get(i, j) - b.get(i, j);
            result.set(i, j, sub);
        }
    }

    return result;
}

void Matrix::add(Matrix other) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            float current = this->get(i, j);
            this->set(i, j, current + other.get(i, j));
        }
    }
}

void Matrix::multiply(Matrix other) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float current = this->get(i, j);
            this->set(i, j, current * other.get(i, j));
        }
    }
}

Matrix Matrix::transpose(Matrix a) {
    Matrix result(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            float current = a.get(i, j);
            result.set(j, i, current);
        }
    }
    return result;
}

Matrix Matrix::product(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        //some issue has been made
    }
    else {
        Matrix result(a.rows, b.cols);
        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                float sum = 0;
                for (int k = 0; k < a.cols; k++)
                {
                    sum += a.get(i, k) * b.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }
}

float Matrix::get(int y, int x) {
    int index = x + y * cols;
    if (index < cols * rows) {
        return this->values[index];
    }
    else {
        return 0;
    }
    
}

void Matrix::set(int y, int x, float val) {
    int index = x + y * cols;
    if (index < cols * rows) {
        this->values[index] = val;
    }
    else {
        this->values[index] = 0;
    }
}