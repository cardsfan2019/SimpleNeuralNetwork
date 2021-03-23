#pragma once
#include "Matrix.h"

class NeuralNetwork {
public:
    float sigmoid(float x);
    float dsigmoid(float x);

    float tanh(float x);

    float dtanh(float x);

    float mut(float val, float rate);

    void mutate(float rate, int rows, int cols);

    void setLearingrate(float rate);

    float* feedforward(float* inputArray, int length);

    void train(float inputArray[], float targetArray[], int length);

    int inputNodes, hiddenNodes, outputNodes;

    float learningRate = 0.1;

    Matrix values;
    Matrix ihWeights;
    Matrix hoWeights;
    Matrix hBias;
    Matrix oBias;
    Matrix input;
    Matrix hidden;
    Matrix output;

    NeuralNetwork(int input, int hidden, int output, float lr);
};